// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.feature.roommain;

import android.content.Context;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.volcengine.vertcdemo.common.SolutionToast;
import com.volcengine.vertcdemo.common.BaseDialog;
import com.volcengine.vertcdemo.common.IAction;
import com.volcengine.vertcdemo.core.net.IRequestCallback;
import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochat.bean.GetAnchorsEvent;
import com.volcengine.vertcdemo.videochat.bean.VideoChatResponse;
import com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo;
import com.volcengine.vertcdemo.videochat.core.Constants;
import com.volcengine.vertcdemo.videochat.core.VideoChatDataManager;
import com.volcengine.vertcdemo.videochat.core.VideoChatRTCManager;
import com.volcengine.vertcdemo.videochat.databinding.DialogVideoChatRemoteAnchorBinding;

import java.util.ArrayList;
import java.util.List;

/**
 * 远端主播列表对话框
 */
public class RemoteAnchorsDialog extends BaseDialog {
    private static final String TAG = "RemoteAnchors";

    private DialogVideoChatRemoteAnchorBinding mViewBinding;
    private RemoteHostAdapter mRemoteAnchorsAdapter;

    private final IRequestCallback<GetAnchorsEvent> mGetOnlineAnchorCallback = new IRequestCallback<GetAnchorsEvent>() {
        @Override
        public void onSuccess(GetAnchorsEvent data) {
            setRemoteHostList(data.anchorList);
        }

        @Override
        public void onError(int errorCode, String message) {
            String prefix = getContext().getString(R.string.get_data_remote_host_error);
            SolutionToast.show(prefix + message);
             mViewBinding.emptyView.setVisibility(View.VISIBLE);
        }
    };

    private final IAction<VideoChatUserInfo> mUserInfoOption = userInfo -> {
        if (userInfo == null) {
            return;
        }
        int status = userInfo.userStatus;
        if (status != VideoChatUserInfo.USER_STATUS_NORMAL) {
            SolutionToast.show(R.string.host_busy);
        }
        String uName = userInfo.userName;
        IRequestCallback<VideoChatResponse> callback = new IRequestCallback<VideoChatResponse>() {
            @Override
            public void onSuccess(VideoChatResponse data) {
                Log.e(TAG, "inviteAnchor success!");
                if (!TextUtils.isEmpty(uName)) {
                    SolutionToast.show(getContext().getString(R.string.invitation_sent_xxx_waiting, uName));
                }
                VideoChatDataManager.ins().selfInviteStatus = VideoChatDataManager.INTERACT_STATUS_INVITING_PK;
                cancel();
            }

            @Override
            public void onError(int errorCode, String message) {
                if (errorCode == Constants.ErrorCode.CODE_550 || errorCode == Constants.ErrorCode.CODE_551) {
                    SolutionToast.show(R.string.host_busy);
                }
                Log.e(TAG, "inviteAnchor error code:" + errorCode + ",message:" + message);
                cancel();
            }
        };
        if (status == VideoChatUserInfo.USER_STATUS_NORMAL) {
            VideoChatRTCManager.ins().getRTSClient().inviteAnchor(VideoChatDataManager.ins().selfUserInfo.roomId,
                    VideoChatDataManager.ins().selfUserInfo.userId,
                    userInfo.roomId, userInfo.userId, -1, callback);
        }
    };

    public RemoteAnchorsDialog(Context context) {
        super(context);
    }

    public RemoteAnchorsDialog(Context context, int theme) {
        super(context, theme);
    }

    protected RemoteAnchorsDialog(Context context, boolean cancelable, OnCancelListener cancelListener) {
        super(context, cancelable, cancelListener);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        mViewBinding = DialogVideoChatRemoteAnchorBinding.inflate(getLayoutInflater());
        setContentView(mViewBinding.getRoot());
        
        super.onCreate(savedInstanceState);
        initView();
        requestRemoteAnchorList();
    }

    private void initView() {
        mViewBinding.remoteHostList.setLayoutManager(new LinearLayoutManager(getContext(), RecyclerView.VERTICAL, false));
        mRemoteAnchorsAdapter = new RemoteHostAdapter(mUserInfoOption);
        mViewBinding.remoteHostList.setAdapter(mRemoteAnchorsAdapter);
    }

    private void requestRemoteAnchorList() {
        VideoChatRTCManager.ins().getRTSClient().getAnchorList(mGetOnlineAnchorCallback);
    }

    private void setRemoteHostList(List<VideoChatUserInfo> users) {
        mRemoteAnchorsAdapter.setData(users);
        if (users == null || users.isEmpty()) {
             mViewBinding.emptyView.setVisibility(View.VISIBLE);
        } else {
             mViewBinding.emptyView.setVisibility(View.GONE);
        }
    }

    private static class RemoteHostAdapter extends RecyclerView.Adapter<RecyclerView.ViewHolder> {
        private final List<VideoChatUserInfo> mData = new ArrayList<>();
        private final IAction<VideoChatUserInfo> mUserOption;

        public RemoteHostAdapter(IAction<VideoChatUserInfo> userOption) {
            mUserOption = userOption;
        }

        @NonNull
        @Override
        public RecyclerView.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
            View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_video_chat_main_audience, parent, false);
            return new RemoteHostViewHolder(view, mUserOption);
        }

        @Override
        public void onBindViewHolder(@NonNull RecyclerView.ViewHolder holder, int position) {
            if (holder instanceof RemoteHostViewHolder) {
                ((RemoteHostViewHolder) holder).bind(mData.get(position));
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

        private static class RemoteHostViewHolder extends RecyclerView.ViewHolder {
            private VideoChatUserInfo mUserInfo;
            private final TextView mUserNamePrefix;
            private final TextView mUserName;
            private final TextView mUserOption;

            public RemoteHostViewHolder(@NonNull View itemView, IAction<VideoChatUserInfo> userInfoIAction) {
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
                    mUserOption.setText(R.string.in_pk);
                    mUserOption.setBackgroundResource(R.drawable.item_video_listener_option_unselected_bg);
                } else if (status == VideoChatUserInfo.USER_STATUS_INVITING) {
                    mUserOption.setText(R.string.video_chat_invited);
                    mUserOption.setBackgroundResource(R.drawable.item_video_listener_option_unselected_bg);
                } else if (status == VideoChatUserInfo.USER_STATUS_APPLYING) {
                    mUserOption.setText(R.string.accept);
                    mUserOption.setBackgroundResource(R.drawable.item_video_listener_option_selected_bg);
                } else {
                    mUserOption.setText(R.string.video_host_invite);
                    mUserOption.setBackgroundResource(R.drawable.item_video_listener_option_selected_bg);
                }
            }
        }
    }
}
