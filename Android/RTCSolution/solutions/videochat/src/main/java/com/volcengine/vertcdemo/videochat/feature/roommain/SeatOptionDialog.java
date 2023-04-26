// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.feature.roommain;

import static com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo.MIC_STATUS_ON;
import static com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo.USER_ROLE_HOST;
import static com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo.USER_STATUS_INTERACT;
import static com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo.USER_STATUS_NORMAL;

import android.content.Context;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.volcengine.vertcdemo.common.BaseDialog;
import com.volcengine.vertcdemo.common.SolutionCommonDialog;
import com.volcengine.vertcdemo.common.SolutionToast;
import com.volcengine.vertcdemo.core.SolutionDataManager;
import com.volcengine.vertcdemo.core.eventbus.SolutionDemoEventManager;
import com.volcengine.vertcdemo.core.net.ErrorTool;
import com.volcengine.vertcdemo.core.net.IRequestCallback;
import com.volcengine.vertcdemo.utils.Utils;
import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochat.bean.AudienceChangedEvent;
import com.volcengine.vertcdemo.videochat.bean.InteractChangedEvent;
import com.volcengine.vertcdemo.videochat.bean.MediaChangedEvent;
import com.volcengine.vertcdemo.videochat.bean.ReplyMicOnEvent;
import com.volcengine.vertcdemo.videochat.bean.SeatChangedEvent;
import com.volcengine.vertcdemo.videochat.bean.VideoChatResponse;
import com.volcengine.vertcdemo.videochat.bean.VideoChatSeatInfo;
import com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo;
import com.volcengine.vertcdemo.videochat.core.VideoChatDataManager;
import com.volcengine.vertcdemo.videochat.core.VideoChatRTCManager;
import com.volcengine.vertcdemo.videochat.databinding.DialogVideoChatSeatOptionBinding;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

/**
 * 座位管理对话框
 */
@SuppressWarnings("unused")
public class SeatOptionDialog extends BaseDialog {

    static final int MIC_OPTION_ON = 1;
    static final int SEAT_STATUS_LOCKED = 0;
    static final int SEAT_STATUS_UNLOCKED = 1;

    private DialogVideoChatSeatOptionBinding mViewBinding;
    private String mRoomId;
    private VideoChatSeatInfo mSeatInfo;
    private @VideoChatUserInfo.UserRole
    int mSelfRole;
    private @VideoChatUserInfo.UserStatus
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
        mViewBinding = DialogVideoChatSeatOptionBinding.inflate(getLayoutInflater());
        setContentView(mViewBinding.getRoot());

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
        mViewBinding.optionInteract.setOnClickListener((v) -> onClickInteract());
        mViewBinding.optionMicSwitch.setOnClickListener((v) -> onClickMicStatus());
        mViewBinding.optionSeatLock.setOnClickListener((v) -> onClickLockStatus());

        boolean isSelfHost = mSelfRole == USER_ROLE_HOST;

        if (mSeatInfo == null) {
            mViewBinding.optionMicSwitch.setVisibility(View.VISIBLE);
            mViewBinding.optionSeatLock.setVisibility(View.VISIBLE);
            updateInteractStatus(VideoChatDataManager.SEAT_STATUS_UNLOCKED, USER_STATUS_NORMAL, VideoChatUserInfo.USER_ROLE_AUDIENCE);
            updateMicStatus(VideoChatDataManager.SEAT_STATUS_UNLOCKED, MIC_STATUS_ON, isSelfHost, true);
            updateSeatStatus(VideoChatDataManager.SEAT_STATUS_UNLOCKED, false);
        } else {
            VideoChatUserInfo userInfo = mSeatInfo.userInfo;
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
        VideoChatRTCManager.ins().getRTSClient().managerSeat(
                mRoomId, mSeatInfo.seatIndex, option,
                new IRequestCallback<VideoChatResponse>() {
                    @Override
                    public void onSuccess(VideoChatResponse data) {

                    }

                    @Override
                    public void onError(int errorCode, String message) {

                    }
                });
    }

    public void setData(@NonNull String roomId, VideoChatSeatInfo info,
                        @VideoChatUserInfo.UserRole int selfRole,
                        @VideoChatUserInfo.UserStatus int selfStatus) {
        mRoomId = roomId;
        mSelfRole = selfRole;
        mSelfStatus = selfStatus;
        mSeatInfo = info == null ? null : info.deepCopy();
    }

    private void updateInteractStatus(@VideoChatDataManager.SeatStatus int seatStatus,
                                      @VideoChatUserInfo.UserStatus int userStatus,
                                      @VideoChatUserInfo.UserRole int selfRole) {
        int drawableRes = userStatus != USER_STATUS_INTERACT
                ? R.drawable.video_chat_seat_option_interact_on
                : R.drawable.video_chat_seat_option_interact_off;
        Drawable drawable = getContext().getResources().getDrawable(drawableRes);
        drawable.setBounds(0, 0,
                (int) Utils.dp2Px(44), (int) Utils.dp2Px(44));
        mViewBinding.optionInteract.setCompoundDrawables(null, drawable, null, null);
        if (selfRole == USER_ROLE_HOST) {
            if (userStatus != USER_STATUS_INTERACT) {
                mViewBinding.optionInteract.setText(R.string.video_chat_invite_on_mic);
            } else {
                mViewBinding.optionInteract.setText(R.string.video_chat_off_mic);
            }
        } else {
            if (userStatus != USER_STATUS_INTERACT) {
                mViewBinding.optionInteract.setText(R.string.sheet_apply_message);
            } else {
                mViewBinding.optionInteract.setText(R.string.video_chat_off_mic);
            }
        }
        boolean isLocked = seatStatus == SEAT_STATUS_LOCKED;
        mViewBinding.optionInteract.setVisibility(!isLocked ? View.VISIBLE : View.GONE);
    }

    private void updateMicStatus(@VideoChatDataManager.SeatStatus int seatStatus, @VideoChatUserInfo.MicStatus int micStatus, boolean isSelfHost, boolean isEmpty) {
        int drawableRes = micStatus == MIC_STATUS_ON
                ? R.drawable.video_chat_seat_option_mic_on
                : R.drawable.video_chat_seat_option_mic_off;
        Drawable drawable = getContext().getResources().getDrawable(drawableRes);
        drawable.setBounds(0, 0,
                (int) Utils.dp2Px(44), (int) Utils.dp2Px(44));
        mViewBinding.optionMicSwitch.setCompoundDrawables(null, drawable, null, null);
        mViewBinding.optionMicSwitch.setText(micStatus == MIC_OPTION_ON
                ? getContext().getString(R.string.video_chat_mute_mic)
                : getContext().getString(R.string.video_chat_unmute));
        boolean isLocked = seatStatus == SEAT_STATUS_LOCKED;
        mViewBinding.optionMicSwitch.setVisibility(!isLocked && isSelfHost && !isEmpty ? View.VISIBLE : View.GONE);
    }

    private void updateSeatStatus(@VideoChatDataManager.SeatStatus int status, boolean isSelfHost) {
        int drawableRes = status == SEAT_STATUS_UNLOCKED
                ? R.drawable.video_chat_seat_option_locked
                : R.drawable.video_chat_seat_option_unlocked;
        Drawable drawable = getContext().getResources().getDrawable(drawableRes);
        drawable.setBounds(0, 0,
                (int) Utils.dp2Px(44), (int) Utils.dp2Px(44));
        mViewBinding.optionSeatLock.setText(status == SEAT_STATUS_UNLOCKED
                ? getContext().getString(R.string.video_chat_lock_seat)
                : getContext().getString(R.string.video_chat_unlock_seat));

        mViewBinding.optionSeatLock.setCompoundDrawables(null, drawable, null, null);
        mViewBinding.optionSeatLock.setVisibility(isSelfHost ? View.VISIBLE : View.GONE);
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
                if (mSelfStatus == VideoChatUserInfo.USER_STATUS_APPLYING) {
                    SolutionToast.show(R.string.application_sent_host);
                } else if (mSelfStatus == USER_STATUS_INTERACT) {
                    SolutionToast.show(R.string.video_chat_on_mic);
                } else if (mSelfStatus == USER_STATUS_NORMAL) {
                    VideoChatRTCManager.ins().getRTSClient().applyInteract(
                            mRoomId, mSeatInfo.seatIndex,
                            new IRequestCallback<ReplyMicOnEvent>() {
                                @Override
                                public void onSuccess(ReplyMicOnEvent data) {
                                    if (data.needApply) {
                                        SolutionToast.show(R.string.application_sent_host);
                                        VideoChatDataManager.ins().setSelfApply(true);
                                        VideoChatDataManager.ins().selfInviteStatus = VideoChatDataManager.INTERACT_STATUS_INVITING_CHAT;
                                    }
                                }

                                @Override
                                public void onError(int errorCode, String message) {
                                    SolutionToast.show(ErrorTool.getErrorMessageByErrorCode(errorCode, message));
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
                VideoChatRTCManager.ins().getRTSClient().finishInteract(mRoomId, mSeatInfo.seatIndex,
                        new IRequestCallback<VideoChatResponse>() {
                            @Override
                            public void onSuccess(VideoChatResponse data) {

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
        VideoChatUserInfo userInfo = mSeatInfo.userInfo;
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
            SolutionCommonDialog dialog = new SolutionCommonDialog(getContext());
            dialog.setMessage(getContext().getString(R.string.sure_lock_seat));
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
        VideoChatUserInfo userInfo = mSeatInfo.userInfo;
        if (userInfo != null && TextUtils.equals(userInfo.userId, userId)) {
            dismiss();
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onAudienceChangedBroadcast(AudienceChangedEvent event) {
        checkIfClose(event.userInfo.userId);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onInteractChangedBroadcast(InteractChangedEvent event) {
        checkIfClose(event.userInfo.userId);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMediaChangedBroadcast(MediaChangedEvent event) {
        checkIfClose(event.userInfo.userId);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onSeatChangedBroadcast(SeatChangedEvent event) {
        if (event.seatId == mSeatInfo.seatIndex && event.type != mSeatInfo.status) {
            dismiss();
        }
    }
}
