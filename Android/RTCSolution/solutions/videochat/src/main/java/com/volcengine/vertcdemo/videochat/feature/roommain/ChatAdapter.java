// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.feature.roommain;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.volcengine.vertcdemo.videochat.R;

import java.util.ArrayList;
import java.util.List;

public class ChatAdapter extends RecyclerView.Adapter<RecyclerView.ViewHolder> {

    private final List<String> mMsgList = new ArrayList<>();

    @NonNull
    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_video_chat_chat,
                parent, false);
        return new ChatViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull RecyclerView.ViewHolder holder, int position) {
        if (holder instanceof ChatViewHolder) {
            ((ChatViewHolder) holder).bind(mMsgList.get(position));
        }
    }

    @Override
    public int getItemCount() {
        return mMsgList.size();
    }

    public void addChatMsg(String info) {
        if (info == null) {
            return;
        }
        mMsgList.add(info);
        notifyItemInserted(mMsgList.size() - 1);
    }

    private static class ChatViewHolder extends RecyclerView.ViewHolder {

        private final TextView mChatTv;

        public ChatViewHolder(@NonNull View itemView) {
            super(itemView);
            mChatTv = (TextView) itemView;
        }

        public void bind(String msg) {
            mChatTv.setText(msg);
        }
    }
}

