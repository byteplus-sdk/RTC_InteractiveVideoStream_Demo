/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.feature.roommain;

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

import com.ss.video.rtc.demo.basic_module.utils.SafeToast;
import com.volcengine.vertcdemo.common.BaseDialog;
import com.volcengine.vertcdemo.common.IAction;
import com.volcengine.vertcdemo.core.net.IRequestCallback;
import com.volcengine.vertcdemo.core.net.rtm.RTMBizResponse;
import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochatdemo.bean.GetAnchorsResponse;
import com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo;
import com.volcengine.vertcdemo.videochatdemo.core.VideoChatDataManager;
import com.volcengine.vertcdemo.videochatdemo.core.VideoChatRTCManager;

import java.util.ArrayList;
import java.util.List;

public class RemoteAnchorsManagerDialog extends BaseDialog {
    private static final String TAG = "RemoteAnchors";
    private View mEmptyView;
    private RemoteHostAdapter mRemoteAnchorsAdapter;


    private final IRequestCallback<GetAnchorsResponse> mGetOnlineAnchorCallback = new IRequestCallback<GetAnchorsResponse>() {
        @Override
        public void onSuccess(GetAnchorsResponse data) {
            setRemoteHostList(data.anchorList);
        }

        @Override
        public void onError(int errorCode, String message) {
            SafeToast.show(getContext().getString(R.string.cant_get_remote_host_error) + message);
            mEmptyView.setVisibility(View.VISIBLE);
        }
    };


    private final IAction<VCUserInfo> mUserInfoOption = userInfo -> {
        if (userInfo == null) {
            return;
        }
        int status = userInfo.userStatus;
        if (status != VCUserInfo.USER_STATUS_NORMAL) {
            SafeToast.show(R.string.invite_user_busy);
        }
        String uName = userInfo.userName;
        IRequestCallback<RTMBizResponse> callback = new IRequestCallback<RTMBizResponse>() {
            @Override
            public void onSuccess(RTMBizResponse data) {
                Log.e(TAG, "inviteAnchor success!");
                if (!TextUtils.isEmpty(uName)) {
                    SafeToast.show(getContext().getString(R.string.invitation_has_sent_info, uName));
                }
                VideoChatDataManager.ins().selfInviteStatus = VideoChatDataManager.INTERACT_STATUS_INVITING_PK;
                cancel();
            }

            @Override
            public void onError(int errorCode, String message) {
                if (errorCode == 550 || errorCode == 551) {
                    SafeToast.show(R.string.invite_user_busy);
                }
                Log.e(TAG, "inviteAnchor error code:" + errorCode + ",message:" + message);
                cancel();
            }
        };
        if (status == VCUserInfo.USER_STATUS_NORMAL) {
            VideoChatRTCManager.ins().getRTMClient().inviteAnchor(VideoChatDataManager.ins().selfUserInfo.roomId,
                    VideoChatDataManager.ins().selfUserInfo.userId,
                    userInfo.roomId, userInfo.userId, -1, callback);
        }
    };

    public RemoteAnchorsManagerDialog(Context context) {
        super(context);
    }

    public RemoteAnchorsManagerDialog(Context context, int theme) {
        super(context, theme);
    }

    protected RemoteAnchorsManagerDialog(Context context, boolean cancelable, OnCancelListener cancelListener) {
        super(context, cancelable, cancelListener);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        setContentView(R.layout.dialog_video_chat_remote_host_manager);
        super.onCreate(savedInstanceState);
        initView();
        requestRemoteAnchorList();
    }

    private void initView() {
        RecyclerView remoteAnchorsRv = findViewById(R.id.remote_host_list);
        mEmptyView = findViewById(R.id.empty_view);
        remoteAnchorsRv.setLayoutManager(new LinearLayoutManager(getContext(), RecyclerView.VERTICAL, false));
        mRemoteAnchorsAdapter = new RemoteHostAdapter(mUserInfoOption);
        remoteAnchorsRv.setAdapter(mRemoteAnchorsAdapter);
    }

    public void setData(String roomId, boolean allowApply, boolean hasNewApply, int seatId) {

    }

    @Override
    public void show() {
        super.show();
    }

    @Override
    public void dismiss() {
        super.dismiss();
    }

    private void requestRemoteAnchorList() {
        VideoChatRTCManager.ins().getRTMClient().getAnchorList(mGetOnlineAnchorCallback);
    }

    private void setRemoteHostList(List<VCUserInfo> users) {
        mRemoteAnchorsAdapter.setData(users);
        if (users == null || users.isEmpty()) {
            mEmptyView.setVisibility(View.VISIBLE);
        } else {
            mEmptyView.setVisibility(View.GONE);
        }
    }

    private static class RemoteHostAdapter extends RecyclerView.Adapter<RecyclerView.ViewHolder> {
        private final List<VCUserInfo> mData = new ArrayList<>();
        private final IAction<VCUserInfo> mUserOption;

        public RemoteHostAdapter(IAction<VCUserInfo> userOption) {
            mUserOption = userOption;
        }

        @NonNull
        @Override
        public RecyclerView.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
            View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_video_chat_demo_main_audience, parent, false);
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

        public void setData(@Nullable List<VCUserInfo> users) {
            mData.clear();
            if (users != null) {
                mData.addAll(users);
            }
            notifyDataSetChanged();
        }

        public void addOrUpdateUser(VCUserInfo userInfo) {
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

        public void removeUser(VCUserInfo userInfo) {
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
            private VCUserInfo mUserInfo;
            private final TextView mUserNamePrefix;
            private final TextView mUserName;
            private final TextView mUserOption;

            public RemoteHostViewHolder(@NonNull View itemView, IAction<VCUserInfo> userInfoIAction) {
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

            public void bind(VCUserInfo userInfo) {
                mUserInfo = userInfo;
                if (userInfo != null) {
                    String userName = userInfo.userName;
                    mUserNamePrefix.setText(TextUtils.isEmpty(userName) ? "" : userName.substring(0, 1));
                    mUserName.setText(userName);
                    updateOptionByStatus(userInfo.userStatus);
                } else {
                    mUserNamePrefix.setText("");
                    mUserName.setText("");
                    updateOptionByStatus(VCUserInfo.USER_STATUS_NORMAL);
                }
            }

            private void updateOptionByStatus(@VCUserInfo.UserStatus int status) {
                if (status == VCUserInfo.USER_STATUS_INTERACT) {
                    mUserOption.setText(R.string.pk_ing);
                    mUserOption.setBackgroundResource(R.drawable.item_video_listener_option_unselected_bg);
                } else if (status == VCUserInfo.USER_STATUS_INVITING) {
                    mUserOption.setText(R.string.inviting_btn);
                    mUserOption.setBackgroundResource(R.drawable.item_voice_listener_option_unselected_bg);
                } else if (status == VCUserInfo.USER_STATUS_APPLYING) {
                    mUserOption.setText(R.string.accept);
                    mUserOption.setBackgroundResource(R.drawable.item_voice_listener_option_selected_bg);
                } else {
                    mUserOption.setText(R.string.invite_cohost);
                    mUserOption.setBackgroundResource(R.drawable.item_voice_listener_option_selected_bg);
                }
            }
        }
    }
}
