/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatDialog;

import com.volcengine.vertcdemo.videochat.R;

public class CommonDialog extends AppCompatDialog {
    private TextView mTitleTv;
    private TextView mMessageTv;
    private TextView mPositiveBtn;
    private TextView mNegativeBtn;
    private View mDivider;

    public CommonDialog(Context context) {
        super(context, R.style.CommonDialog);
        this.setCancelable(true);
        LayoutInflater inflater = LayoutInflater.from(this.getContext());
        View view = inflater.inflate(R.layout.dialog_common_video, (ViewGroup)null);
        this.mTitleTv = (TextView)view.findViewById(R.id.dialog_title_tv);
        this.mMessageTv = (TextView)view.findViewById(R.id.dialog_msg_tv);
        this.mPositiveBtn = (TextView)view.findViewById(R.id.dialog_positive_btn);
        this.mNegativeBtn = (TextView)view.findViewById(R.id.dialog_negative_btn);
        this.mDivider = view.findViewById(R.id.dialog_btn_divider);
        this.setContentView(view, new ViewGroup.LayoutParams(-1, -2));
        view.setOnClickListener((v) -> {
            this.dismiss();
        });
    }

    public void setMessage(String txt) {
        this.mMessageTv.setText(txt);
    }

    public void setNegativeBtnText(int text) {
        this.mNegativeBtn.setText(text);
    }

    public void setPositiveBtnText(int text) {
        this.mPositiveBtn.setText(text);
    }

    public void setNegativeListener(View.OnClickListener listener) {
        this.mDivider.setVisibility(View.VISIBLE);
        this.mNegativeBtn.setVisibility(View.VISIBLE);
        this.mNegativeBtn.setOnClickListener(listener);
    }

    public void setPositiveListener(View.OnClickListener listener) {
        this.mPositiveBtn.setOnClickListener(listener);
    }
}

