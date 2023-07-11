// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.feature.roommain;

import static com.volcengine.vertcdemo.videochat.bean.VideoChatRoomInfo.ROOM_STATUS_CHATTING;

import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.IntDef;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.volcengine.vertcdemo.common.SolutionToast;
import com.volcengine.vertcdemo.common.BaseDialog;
import com.volcengine.vertcdemo.common.IAction;
import com.volcengine.vertcdemo.core.eventbus.SolutionDemoEventManager;
import com.volcengine.vertcdemo.core.net.ErrorTool;
import com.volcengine.vertcdemo.core.net.IRequestCallback;
import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochat.bean.AudienceApplyEvent;
import com.volcengine.vertcdemo.videochat.bean.AudienceChangedEvent;
import com.volcengine.vertcdemo.videochat.bean.GetAudienceEvent;
import com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo;
import com.volcengine.vertcdemo.videochat.bean.VideoChatResponse;
import com.volcengine.vertcdemo.videochat.core.VideoChatDataManager;
import com.volcengine.vertcdemo.videochat.core.VideoChatRTCManager;
import com.volcengine.vertcdemo.videochat.databinding.DialogVideoChatAudienceManagerBinding;
import com.volcengine.vertcdemo.videochat.event.UserStatusChangedEvent;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.util.ArrayList;
import java.util.List;

/**
 * 观众列表管理对话框
 */
@SuppressWarnings("unused")
public class AudienceManagerDialog extends BaseDialog {

    public static final int TABLE_ONLINE_USERS = 0;
    public static final int TABLE_APPLY_USERS = 1;

    public static final int SEAT_ID_BY_SERVER = -1;

    @IntDef({TABLE_ONLINE_USERS, TABLE_APPLY_USERS})
    @Retention(RetentionPolicy.SOURCE)
    public @interface UserManagerTable {
    }

    private final int SELECTED_TEXT_COLOR = Color.parseColor("#4080FF");

    private DialogVideoChatAudienceManagerBinding mViewBinding;

    @UserManagerTable
    private int mTable = TABLE_ONLINE_USERS;
    private String mRoomId;
    private boolean hasNewApply;
    private int mSeatId = SEAT_ID_BY_SERVER;
    private final IRequestCallback<GetAudienceEvent> mGetOnlineUsersCallback = new IRequestCallback<GetAudienceEvent>() {
        @Override
        public void onSuccess(GetAudienceEvent data) {
            setOnlineUserList(data.audienceList);
        }

        @Override
        public void onError(int errorCode, String message) {
            mViewBinding.managerOnlineEmptyListView.setVisibility(View.VISIBLE);
        }
    };
    private final IRequestCallback<GetAudienceEvent> mGetApplyUsersCallback = new IRequestCallback<GetAudienceEvent>() {
        @Override
        public void onSuccess(GetAudienceEvent data) {
            setApplyUserList(data.audienceList);

            boolean hasNewApply = data.audienceList != null && !data.audienceList.isEmpty();
            setHasNewApply(hasNewApply);
        }

        @Override
        public void onError(int errorCode, String message) {
            mViewBinding.managerApplyEmptyListView.setVisibility(View.VISIBLE);
        }
    };

    private final IAction<VideoChatUserInfo> mUserInfoOption = userInfo -> {
        if (userInfo == null) {
            return;
        }
        int status = userInfo.userStatus;
        IRequestCallback<VideoChatResponse> callback = new IRequestCallback<VideoChatResponse>() {
            @Override
            public void onSuccess(VideoChatResponse data) {
                if (userInfo.userStatus != VideoChatUserInfo.USER_STATUS_APPLYING) {
                    SolutionToast.show(R.string.invitation_audience_waiting);
                    VideoChatDataManager.ins().selfInviteStatus = VideoChatDataManager.INTERACT_STATUS_INVITING_CHAT;
                } else {
                    /*
                    如果当前只有一个人在申请，同意后需要去掉红点
                     */
                    if (mApplyAudienceAdapter.getItemCount() == 1) {
                        setHasNewApply(false);
                    }
                }
                cancel();
            }

            @Override
            public void onError(int errorCode, String message) {
                SolutionToast.show(ErrorTool.getErrorMessageByErrorCode(errorCode, message));
                cancel();
            }
        };
        if (status == VideoChatUserInfo.USER_STATUS_NORMAL) {
            VideoChatRTCManager.ins().getRTSClient().inviteInteract(mRoomId, userInfo.userId, mSeatId, callback);
        } else if (status == VideoChatUserInfo.USER_STATUS_APPLYING) {
            VideoChatRTCManager.ins().getRTSClient().agreeApply(mRoomId, userInfo.userId, userInfo.roomId, callback);
        }
    };
    private ICloseChatRoom mICloseChatRoom;

    private final AudienceManagerAdapter mOnlineAudienceAdapter = new AudienceManagerAdapter(mUserInfoOption);
    private final AudienceManagerAdapter mApplyAudienceAdapter = new AudienceManagerAdapter(mUserInfoOption);

    public AudienceManagerDialog(Context context) {
        super(context);
    }

    public AudienceManagerDialog(Context context, int theme) {
        super(context, theme);
    }

    protected AudienceManagerDialog(Context context, boolean cancelable, OnCancelListener cancelListener) {
        super(context, cancelable, cancelListener);
    }

    public void setICloseChatRoom(ICloseChatRoom iCloseChatRoom) {
        this.mICloseChatRoom = iCloseChatRoom;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        mViewBinding = DialogVideoChatAudienceManagerBinding.inflate(getLayoutInflater());
        setContentView(mViewBinding.getRoot());

        super.onCreate(savedInstanceState);
        initView();
    }

    private void initView() {
        mViewBinding.managerOnlineList.setLayoutManager(new LinearLayoutManager(getContext(), RecyclerView.VERTICAL, false));
        mViewBinding.managerApplyList.setLayoutManager(new LinearLayoutManager(getContext(), RecyclerView.VERTICAL, false));
        mViewBinding.managerOnlineList.setAdapter(mOnlineAudienceAdapter);
        mViewBinding.managerApplyList.setAdapter(mApplyAudienceAdapter);

        mViewBinding.managerOnlineTab.setOnClickListener((v) -> changeTable(TABLE_ONLINE_USERS));
        mViewBinding.managerApplyTab.setOnClickListener((v) -> changeTable(TABLE_APPLY_USERS));
        mViewBinding.closeRoomChatTv.setOnClickListener(v -> {
            if (mICloseChatRoom == null) return;
            mICloseChatRoom.closeChatRoom();
            dismiss();
        });
        updateCloseChatRoomBtn();
    }

    public void setData(String roomId, boolean hasNewApply, int seatId) {
        mRoomId = roomId;
        mSeatId = seatId;
        setHasNewApply(hasNewApply);
    }

    @Override
    public void show() {
        super.show();
        SolutionDemoEventManager.register(this);
        changeTable(hasNewApply ? TABLE_APPLY_USERS : TABLE_ONLINE_USERS);
        setHasNewApply(hasNewApply);
    }

    @Override
    public void dismiss() {
        super.dismiss();
        SolutionDemoEventManager.unregister(this);
    }

    private void changeTable(@UserManagerTable int table) {
        final int normalTextColor = Color.WHITE;
        mTable = table;
        if (table == TABLE_ONLINE_USERS) {
            requestOnlineUserList();
            mViewBinding.managerOnlineTab.setTextColor(SELECTED_TEXT_COLOR);
            mViewBinding.managerApplyTab.setTextColor(normalTextColor);
            mViewBinding.managerOnlineList.setVisibility(View.VISIBLE);
            mViewBinding.managerOnlineEmptyListView.setVisibility(View.GONE);
            mViewBinding.managerApplyList.setVisibility(View.GONE);
            mViewBinding.managerApplyEmptyListView.setVisibility(View.GONE);

            mViewBinding.managerOnlineIndicator.setVisibility(View.VISIBLE);
            mViewBinding.managerApplyIndicator.setVisibility(View.INVISIBLE);
        } else if (table == TABLE_APPLY_USERS) {
            requestApplyUserList();
            mViewBinding.managerOnlineTab.setTextColor(normalTextColor);
            mViewBinding.managerApplyTab.setTextColor(SELECTED_TEXT_COLOR);
            mViewBinding.managerOnlineList.setVisibility(View.GONE);
            mViewBinding.managerOnlineEmptyListView.setVisibility(View.GONE);
            mViewBinding.managerApplyList.setVisibility(View.VISIBLE);
            mViewBinding.managerApplyEmptyListView.setVisibility(View.GONE);

            mViewBinding.managerOnlineIndicator.setVisibility(View.INVISIBLE);
            mViewBinding.managerApplyIndicator.setVisibility(View.VISIBLE);
        }
    }

    private void requestOnlineUserList() {
        VideoChatRTCManager.ins().getRTSClient().requestAudienceList(mRoomId, mGetOnlineUsersCallback);
    }

    private void requestApplyUserList() {
        VideoChatRTCManager.ins().getRTSClient().requestApplyAudienceList(mRoomId, mGetApplyUsersCallback);
    }

    private void setOnlineUserList(List<VideoChatUserInfo> users) {
        mOnlineAudienceAdapter.setData(users);
        if (users == null || users.isEmpty()) {
            mViewBinding.managerOnlineEmptyListView.setVisibility(View.VISIBLE);
        } else {
            mViewBinding.managerOnlineEmptyListView.setVisibility(View.GONE);
        }
    }

    private void setApplyUserList(List<VideoChatUserInfo> users) {
        mApplyAudienceAdapter.setData(users);
        if (users == null || users.isEmpty()) {
            mViewBinding.managerApplyEmptyListView.setVisibility(View.VISIBLE);
        } else {
            mViewBinding.managerApplyEmptyListView.setVisibility(View.GONE);
        }
    }

    public void setHasNewApply(boolean hasNewApply) {
        this.hasNewApply = hasNewApply;
        VideoChatDataManager.ins().setNewApply(hasNewApply);
        AudienceApplyEvent broadcast = new AudienceApplyEvent();
        broadcast.hasNewApply = hasNewApply;
        SolutionDemoEventManager.post(broadcast);
        if (isShowing()) {
            mViewBinding.managerApplyRedDot.setVisibility(hasNewApply ? View.VISIBLE : View.INVISIBLE);
        }
    }

    /**
     * 用户状态发生变化事件
     *
     * @param event 事件
     */
    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onUserStatusChangedEvent(UserStatusChangedEvent event) {
        if (event.status == VideoChatUserInfo.USER_STATUS_NORMAL
                || event.status == VideoChatUserInfo.USER_STATUS_INVITING) {
            mOnlineAudienceAdapter.addOrUpdateUser(event.userInfo);
            mApplyAudienceAdapter.removeUser(event.userInfo);
        } else if (event.status == VideoChatUserInfo.USER_STATUS_APPLYING) {
            mOnlineAudienceAdapter.removeUser(event.userInfo);
            mApplyAudienceAdapter.addOrUpdateUser(event.userInfo);
        } else if (event.status == VideoChatUserInfo.USER_STATUS_INTERACT) {
            mOnlineAudienceAdapter.addOrUpdateUser(event.userInfo);
            mApplyAudienceAdapter.removeUser(event.userInfo);
            if (mApplyAudienceAdapter.getItemCount() == 0) {
                setHasNewApply(false);
            }
        }
        updateEmptyViewVis();
        updateCloseChatRoomBtn();
    }

    /**
     * 用户加入/离开事件
     *
     * @param event 事件
     */
    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onAudienceChangedBroadcast(AudienceChangedEvent event) {
        if (event.isJoin) {
            mOnlineAudienceAdapter.addOrUpdateUser(event.userInfo);
        } else {
            mOnlineAudienceAdapter.removeUser(event.userInfo);
            mApplyAudienceAdapter.removeUser(event.userInfo);
        }
        if (mTable == TABLE_APPLY_USERS) {
            if (mApplyAudienceAdapter.getItemCount() == 0) {
                setApplyUserList(null);
                setHasNewApply(false);
            }
        } else {
            if (mOnlineAudienceAdapter.getItemCount() == 0) {
                setOnlineUserList(null);
            }
        }
        updateEmptyViewVis();
        updateCloseChatRoomBtn();
    }

    private void updateEmptyViewVis() {
        if (mTable == TABLE_APPLY_USERS && mApplyAudienceAdapter != null) {
            int size = mApplyAudienceAdapter.getItemCount();
            mViewBinding.managerApplyEmptyListView.setVisibility(size > 0 ? View.GONE : View.VISIBLE);
        } else if (mTable == TABLE_ONLINE_USERS && mOnlineAudienceAdapter != null) {
            int size = mOnlineAudienceAdapter.getItemCount();
            mViewBinding.managerOnlineEmptyListView.setVisibility(size > 0 ? View.GONE : View.VISIBLE);
        }
    }

    private void updateCloseChatRoomBtn() {
        if (VideoChatDataManager.ins().roomInfo.status == ROOM_STATUS_CHATTING
                && mViewBinding.closeRoomChatTv.getVisibility() != View.VISIBLE) {
            mViewBinding.closeRoomChatTv.setVisibility(View.VISIBLE);
        } else if (VideoChatDataManager.ins().roomInfo.status != ROOM_STATUS_CHATTING
                && mViewBinding.closeRoomChatTv.getVisibility() != View.GONE) {
            mViewBinding.closeRoomChatTv.setVisibility(View.GONE);
        }
    }

    private static class AudienceManagerAdapter extends RecyclerView.Adapter<RecyclerView.ViewHolder> {

        private final List<VideoChatUserInfo> mData = new ArrayList<>();
        private final IAction<VideoChatUserInfo> mUserOption;

        public AudienceManagerAdapter(IAction<VideoChatUserInfo> userOption) {
            mUserOption = userOption;
        }

        @NonNull
        @Override
        public RecyclerView.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
            View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_video_chat_main_audience, parent, false);
            return new AudienceManagerViewHolder(view, mUserOption);
        }

        @Override
        public void onBindViewHolder(@NonNull RecyclerView.ViewHolder holder, int position) {
            if (holder instanceof AudienceManagerViewHolder) {
                ((AudienceManagerViewHolder) holder).bind(mData.get(position));
            }
        }

        @Override
        public int getItemCount() {
            return mData.size();
        }

        public void setData(@Nullable List<VideoChatUserInfo> users) {
            mData.clear();
            if (users != null) {
                mData.addAll(users);
            }
            notifyDataSetChanged();
        }

        public void addOrUpdateUser(VideoChatUserInfo userInfo) {
            if (userInfo == null || TextUtils.isEmpty(userInfo.userId)) {
                return;
            }
            for (int i = 0; i < mData.size(); i++) {
                if (TextUtils.equals(userInfo.userId, mData.get(i).userId)) {
                    mData.get(i).userStatus = userInfo.userStatus;
                    notifyItemChanged(i);
                    return;
                }
            }
            mData.add(userInfo);
            notifyItemInserted(mData.size() - 1);
        }

        public void removeUser(VideoChatUserInfo userInfo) {
            if (userInfo == null || TextUtils.isEmpty(userInfo.userId)) {
                return;
            }
            for (int i = 0; i < mData.size(); i++) {
                if (TextUtils.equals(userInfo.userId, mData.get(i).userId)) {
                    mData.remove(i);
                    notifyItemRemoved(i);
                    break;
                }
            }
        }

        private static class AudienceManagerViewHolder extends RecyclerView.ViewHolder {
            private VideoChatUserInfo mUserInfo;
            private final TextView mUserNamePrefix;
            private final TextView mUserName;
            private final TextView mUserOption;

            public AudienceManagerViewHolder(@NonNull View itemView, IAction<VideoChatUserInfo> userInfoIAction) {
                super(itemView);
                mUserNamePrefix = itemView.findViewById(R.id.item_voice_chat_demo_user_prefix);
                mUserName = itemView.findViewById(R.id.item_voice_chat_demo_user_name);
                mUserOption = itemView.findViewById(R.id.item_voice_chat_demo_user_option);
                mUserOption.setOnClickListener((v) -> {
                    if (mUserInfo != null && userInfoIAction != null) {
                        userInfoIAction.act(mUserInfo);
                    }
                });
            }

            public void bind(VideoChatUserInfo userInfo) {
                mUserInfo = userInfo;
                if (userInfo != null) {
                    String userName = userInfo.userName;
                    mUserNamePrefix.setText(TextUtils.isEmpty(userName) ? "" : userName.substring(0, 1));
                    mUserName.setText(userName);
                    updateOptionByStatus(userInfo.userStatus);
                } else {
                    mUserNamePrefix.setText("");
                    mUserName.setText("");
                    updateOptionByStatus(VideoChatUserInfo.USER_STATUS_NORMAL);
                }
            }

            private void updateOptionByStatus(@VideoChatUserInfo.UserStatus int status) {
                if (status == VideoChatUserInfo.USER_STATUS_INTERACT) {
                    mUserOption.setText(R.string.video_chat_on_mic);
                    mUserOption.setBackgroundResource(R.drawable.item_video_listener_option_unselected_bg);
                } else if (status == VideoChatUserInfo.USER_STATUS_INVITING) {
                    mUserOption.setText(R.string.video_chat_invited);
                    mUserOption.setBackgroundResource(R.drawable.item_video_listener_option_unselected_bg);
                } else if (status == VideoChatUserInfo.USER_STATUS_APPLYING) {
                    mUserOption.setText(R.string.video_chat_agree);
                    mUserOption.setBackgroundResource(R.drawable.item_video_listener_option_selected_bg);
                } else {
                    mUserOption.setText(R.string.video_chat_invite_on_mic);
                    mUserOption.setBackgroundResource(R.drawable.item_video_listener_option_selected_bg);
                }
            }
        }
    }

    public interface ICloseChatRoom {
        void closeChatRoom();
    }
}
