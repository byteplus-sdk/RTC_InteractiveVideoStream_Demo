/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.feature.roommain;

import static com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo.MIC_STATUS_ON;
import static com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo.USER_ROLE_HOST;
import static com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo.USER_STATUS_INTERACT;
import static com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo.USER_STATUS_NORMAL;

import android.content.Context;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.ss.video.rtc.demo.basic_module.ui.CommonDialog;
import com.ss.video.rtc.demo.basic_module.utils.SafeToast;
import com.ss.video.rtc.demo.basic_module.utils.Utilities;
import com.volcengine.vertcdemo.common.BaseDialog;
import com.volcengine.vertcdemo.core.SolutionDataManager;
import com.volcengine.vertcdemo.core.eventbus.SolutionDemoEventManager;
import com.volcengine.vertcdemo.core.net.IRequestCallback;
import com.volcengine.vertcdemo.core.net.rtm.RTSBizResponse;
import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochatdemo.bean.AudienceChangedBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.InteractChangedBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.MediaChangedBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.ReplyMicOnResponse;
import com.volcengine.vertcdemo.videochatdemo.bean.SeatChangedBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.VCSeatInfo;
import com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo;
import com.volcengine.vertcdemo.videochatdemo.core.VideoChatDataManager;
import com.volcengine.vertcdemo.videochatdemo.core.VideoChatRTCManager;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

@SuppressWarnings("unused")
public class SeatOptionDialog extends BaseDialog {

    static final int MIC_OPTION_ON = 1;
    static final int SEAT_STATUS_LOCKED = 0;
    static final int SEAT_STATUS_UNLOCKED = 1;

    private TextView mInteractBtn;
    private TextView mMicSwitchBtn;
    private TextView mLockBtn;
    private String mRoomId;
    private VCSeatInfo mSeatInfo;
    private @VCUserInfo.UserRole
    int mSelfRole;
    private @VCUserInfo.UserStatus
    int mSelfStatus;
    private AudienceManagerDialog.ICloseChatRoom mICloseChatRoom;

    public SeatOptionDialog(@NonNull Context context) {
        super(context);
    }

    public SeatOptionDialog(@NonNull Context context, int themeResId) {
        super(context, themeResId);
    }

    protected SeatOptionDialog(@NonNull Context context, boolean cancelable, @Nullable OnCancelListener cancelListener) {
        super(context, cancelable, cancelListener);
    }

    public void setICloseChatRoom(AudienceManagerDialog.ICloseChatRoom mICloseChatRoom) {
        this.mICloseChatRoom = mICloseChatRoom;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        setContentView(R.layout.dialog_voice_chat_seat_option);
        super.onCreate(savedInstanceState);
        initView();
    }

    @Override
    public void show() {
        super.show();
        SolutionDemoEventManager.register(this);
    }

    @Override
    public void dismiss() {
        super.dismiss();
        SolutionDemoEventManager.unregister(this);
    }

    private void initView() {
        mInteractBtn = findViewById(R.id.option_interact);
        mMicSwitchBtn = findViewById(R.id.option_mic_switch);
        mLockBtn = findViewById(R.id.option_seat_lock);

        mInteractBtn.setOnClickListener((v) -> onClickInteract());
        mMicSwitchBtn.setOnClickListener((v) -> onClickMicStatus());
        mLockBtn.setOnClickListener((v) -> onClickLockStatus());

        boolean isSelfHost = mSelfRole == USER_ROLE_HOST;

        if (mSeatInfo == null) {
            mMicSwitchBtn.setVisibility(View.VISIBLE);
            mLockBtn.setVisibility(View.VISIBLE);
            updateInteractStatus(VideoChatDataManager.SEAT_STATUS_UNLOCKED, USER_STATUS_NORMAL, VCUserInfo.USER_ROLE_AUDIENCE);
            updateMicStatus(VideoChatDataManager.SEAT_STATUS_UNLOCKED, MIC_STATUS_ON, isSelfHost, true);
            updateSeatStatus(VideoChatDataManager.SEAT_STATUS_UNLOCKED, false);
        } else {
            VCUserInfo userInfo = mSeatInfo.userInfo;
            if (userInfo == null) {
                updateInteractStatus(mSeatInfo.status, USER_STATUS_NORMAL, mSelfRole);
                updateMicStatus(mSeatInfo.status, MIC_STATUS_ON, isSelfHost, true);
            } else {
                updateInteractStatus(mSeatInfo.status, userInfo.userStatus, mSelfRole);
                updateMicStatus(mSeatInfo.status, userInfo.mic, isSelfHost, false);
            }
            updateSeatStatus(mSeatInfo.status, isSelfHost);
        }
    }

    private void managerSeat(@VideoChatDataManager.SeatOption int option) {
        VideoChatRTCManager.ins().getRTMClient().managerSeat(
                mRoomId, mSeatInfo.seatIndex, option,
                new IRequestCallback<RTSBizResponse>() {
                    @Override
                    public void onSuccess(RTSBizResponse data) {

                    }

                    @Override
                    public void onError(int errorCode, String message) {

                    }
                });
    }

    public void setData(@NonNull String roomId, VCSeatInfo info,
                        @VCUserInfo.UserRole int selfRole,
                        @VCUserInfo.UserStatus int selfStatus) {
        mRoomId = roomId;
        mSelfRole = selfRole;
        mSelfStatus = selfStatus;
        mSeatInfo = info == null ? null : info.deepCopy();
    }

    private void updateInteractStatus(@VideoChatDataManager.SeatStatus int seatStatus,
                                      @VCUserInfo.UserStatus int userStatus,
                                      @VCUserInfo.UserRole int selfRole) {
        int drawableRes = userStatus != USER_STATUS_INTERACT
                ? R.drawable.voice_chat_demo_seat_option_interact_on
                : R.drawable.voice_chat_demo_seat_option_interact_off;
        Drawable drawable = getContext().getResources().getDrawable(drawableRes);
        drawable.setBounds(0, 0,
                (int) Utilities.dip2Px(44), (int) Utilities.dip2Px(44));
        mInteractBtn.setCompoundDrawables(null, drawable, null, null);
        if (selfRole == USER_ROLE_HOST) {
            if (userStatus != USER_STATUS_INTERACT) {
                mInteractBtn.setText(R.string.invite_user_to_be_guest);
            } else {
                mInteractBtn.setText(R.string.remove_co_host_txt);
            }
        } else {
            if (userStatus != USER_STATUS_INTERACT) {
                mInteractBtn.setText(R.string.co_host_text);
            } else {
                mInteractBtn.setText(R.string.remove_co_host_text);
            }
        }
        boolean isLocked = seatStatus == SEAT_STATUS_LOCKED;
        mInteractBtn.setVisibility(!isLocked ? View.VISIBLE : View.GONE);
    }

    private void updateMicStatus(@VideoChatDataManager.SeatStatus int seatStatus, @VCUserInfo.MicStatus int micStatus, boolean isSelfHost, boolean isEmpty) {
        int drawableRes = micStatus == MIC_STATUS_ON
                ? R.drawable.voice_chat_demo_seat_option_mic_on
                : R.drawable.voice_chat_demo_seat_option_mic_off;
        Drawable drawable = getContext().getResources().getDrawable(drawableRes);
        drawable.setBounds(0, 0,
                (int) Utilities.dip2Px(44), (int) Utilities.dip2Px(44));
        mMicSwitchBtn.setCompoundDrawables(null, drawable, null, null);
        mMicSwitchBtn.setText(micStatus == MIC_OPTION_ON ? R.string.mute_txt : R.string.unmute_txt);
        boolean isLocked = seatStatus == SEAT_STATUS_LOCKED;
        mMicSwitchBtn.setVisibility(!isLocked && isSelfHost && !isEmpty ? View.VISIBLE : View.GONE);
    }

    private void updateSeatStatus(@VideoChatDataManager.SeatStatus int status, boolean isSelfHost) {
        int drawableRes = status == SEAT_STATUS_UNLOCKED
                ? R.drawable.voice_chat_demo_seat_option_locked
                : R.drawable.voice_chat_demo_seat_option_unlocked;
        Drawable drawable = getContext().getResources().getDrawable(drawableRes);
        drawable.setBounds(0, 0,
                (int) Utilities.dip2Px(44), (int) Utilities.dip2Px(44));
        mLockBtn.setText(status == SEAT_STATUS_UNLOCKED ? R.string.block_text : R.string.un_block_text);

        mLockBtn.setCompoundDrawables(null, drawable, null, null);
        mLockBtn.setVisibility(isSelfHost ? View.VISIBLE : View.GONE);
    }

    private void onClickInteract() {
        if (mSeatInfo == null) {
            return;
        }
        if (mSeatInfo.userInfo == null) {
            if (mSelfRole == USER_ROLE_HOST) {
                AudienceManagerDialog dialog = new AudienceManagerDialog(getContext());
                dialog.setData(mRoomId, VideoChatDataManager.ins().hasNewApply(), mSeatInfo.seatIndex);
                dialog.setICloseChatRoom(mICloseChatRoom);
                dialog.show();
                dismiss();
            } else {
                if (mSelfStatus == VCUserInfo.USER_STATUS_APPLYING) {
                    SafeToast.show(R.string.already_send_application_msg);
                } else if (mSelfStatus == USER_STATUS_INTERACT) {
                    SafeToast.show(R.string.already_co_host_msg);
                } else if (mSelfStatus == USER_STATUS_NORMAL) {
                    VideoChatRTCManager.ins().getRTMClient().applyInteract(
                            mRoomId, mSeatInfo.seatIndex,
                            new IRequestCallback<ReplyMicOnResponse>() {
                                @Override
                                public void onSuccess(ReplyMicOnResponse data) {
                                    if (data.needApply) {
                                        SafeToast.show(R.string.already_send_application_msg);
                                        VideoChatDataManager.ins().setSelfApply(true);
                                        VideoChatDataManager.ins().selfInviteStatus = VideoChatDataManager.INTERACT_STATUS_INVITING_CHAT;
                                    }
                                }

                                @Override
                                public void onError(int errorCode, String message) {
                                    if (errorCode == 506) {
                                        SafeToast.show(R.string.all_seats_filled_up_txt);
                                    }
                                    if (errorCode == 550 || errorCode == 551) {
                                        SafeToast.show(R.string.invite_user_busy);
                                    }
                                }
                            });
                    dismiss();
                }
            }
        } else {
            boolean isHost = mSelfRole == USER_ROLE_HOST;
            boolean isSelf = TextUtils.equals(mSeatInfo.userInfo.userId,
                    SolutionDataManager.ins().getUserId());
            if (isHost && !isSelf) {
                managerSeat(VideoChatDataManager.SEAT_OPTION_END_INTERACT);
            } else if (!isHost && isSelf) {
                VideoChatRTCManager.ins().getRTMClient().finishInteract(mRoomId, mSeatInfo.seatIndex,
                        new IRequestCallback<RTSBizResponse>() {
                            @Override
                            public void onSuccess(RTSBizResponse data) {

                            }

                            @Override
                            public void onError(int errorCode, String message) {

                            }
                        });
                dismiss();
            }
        }
    }

    private void onClickMicStatus() {
        if (mSeatInfo == null || mSeatInfo.userInfo == null) {
            return;
        }
        VCUserInfo userInfo = mSeatInfo.userInfo;
        int option = userInfo.isMicOn() ? VideoChatDataManager.SEAT_OPTION_MIC_OFF : VideoChatDataManager.SEAT_OPTION_MIC_ON;
        managerSeat(option);
        dismiss();
    }

    private void onClickLockStatus() {
        if (mSeatInfo == null) {
            return;
        }
        if (mSeatInfo.isLocked()) {
            managerSeat(VideoChatDataManager.SEAT_OPTION_UNLOCK);
            dismiss();
        } else {
            CommonDialog dialog = new CommonDialog(getContext());
            dialog.setMessage(getContext().getString(R.string.confirm_remove_co_host_msg));
            dialog.setNegativeListener((vv) -> {
                dialog.dismiss();
                dismiss();
            });
            dialog.setPositiveListener((vv) -> {
                managerSeat(VideoChatDataManager.SEAT_OPTION_LOCK);
                dialog.dismiss();
                dismiss();
            });
            dialog.show();
        }
    }

    private void checkIfClose(String userId) {
        if (TextUtils.isEmpty(userId)) {
            return;
        }
        VCUserInfo userInfo = mSeatInfo.userInfo;
        if (userInfo != null && TextUtils.equals(userInfo.userId, userId)) {
            dismiss();
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onAudienceChangedBroadcast(AudienceChangedBroadcast event) {
        checkIfClose(event.userInfo.userId);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onInteractChangedBroadcast(InteractChangedBroadcast event) {
        checkIfClose(event.userInfo.userId);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMediaChangedBroadcast(MediaChangedBroadcast event) {
        checkIfClose(event.userInfo.userId);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onSeatChangedBroadcast(SeatChangedBroadcast event) {
        if (event.seatId == mSeatInfo.seatIndex && event.type != mSeatInfo.status) {
            dismiss();
        }
    }
}
