/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.common;

import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;

import androidx.annotation.IdRes;
import androidx.annotation.Nullable;

import com.volcengine.vertcdemo.videochat.R;

import java.util.HashMap;
import java.util.Map;

public class VideoChatEffectBeautyLayout extends LinearLayout implements View.OnClickListener {

    private ImageView mNoSelectedBtn;
    private ImageView mWhitenBtn;
    private ImageView mSmoothBtn;
    private ImageView mSharpBtn;
    private ImageView mBigEyeBtn;

    private View mSelectedBtn;
    private IEffectItemChangedListener mEffectItemChangedListener;

    public static final HashMap<Integer, Integer> sSeekBarProgressMap = new HashMap<>();

    static {
        VideoChatEffectBeautyLayout.sSeekBarProgressMap.put(R.id.effect_whiten, 50);
        VideoChatEffectBeautyLayout.sSeekBarProgressMap.put(R.id.effect_smooth, 50);
        VideoChatEffectBeautyLayout.sSeekBarProgressMap.put(R.id.effect_sharp, 50);
        VideoChatEffectBeautyLayout.sSeekBarProgressMap.put(R.id.effect_big_eye, 50);
    }

    public VideoChatEffectBeautyLayout(Context context, IEffectItemChangedListener listener) {
        super(context);
        this.mEffectItemChangedListener = listener;
        initView();
    }

    public VideoChatEffectBeautyLayout(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        initView();
    }

    public VideoChatEffectBeautyLayout(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        initView();
    }

    public void initView() {
        LayoutInflater.from(getContext()).inflate(R.layout.dialog_effect_beauty, this, true);

        mNoSelectedBtn = findViewById(R.id.no_select);
        mNoSelectedBtn.setOnClickListener(this);
        mSelectedBtn = mNoSelectedBtn;
        mWhitenBtn = findViewById(R.id.effect_whiten);
        mWhitenBtn.setOnClickListener(this);
        mSmoothBtn = findViewById(R.id.effect_smooth);
        mSmoothBtn.setOnClickListener(this);
        mSharpBtn = findViewById(R.id.effect_sharp);
        mSharpBtn.setOnClickListener(this);
        mBigEyeBtn = findViewById(R.id.effect_big_eye);
        mBigEyeBtn.setOnClickListener(this);

        if (mLastId == R.id.effect_whiten) {
            updateUI(mWhitenBtn);
        } else if (mLastId == R.id.effect_smooth) {
            updateUI(mSmoothBtn);
        } else if (mLastId == R.id.effect_sharp) {
            updateUI(mSharpBtn);
        } else if (mLastId == R.id.effect_big_eye) {
            updateUI(mBigEyeBtn);
        } else {
            updateUI(mNoSelectedBtn);
        }
        updateStatusByValue();
    }

    private void updateUI(View view) {
        view.setBackgroundResource(R.drawable.effect_btn_selected_bg);
        if (view != mSelectedBtn) {
            mSelectedBtn.setBackgroundResource(R.drawable.effect_btn_normal_bg);
        }
        mSelectedBtn = view;
    }

    public void updateStatusByValue() {
        for (Map.Entry<Integer, Integer> idValue : sSeekBarProgressMap.entrySet()) {
            ImageView view;
            int id = idValue.getKey();
            int value = idValue.getValue() == null ? 0 : idValue.getValue();
            if (id == R.id.effect_whiten) {
                view = mWhitenBtn;
            } else if (id == R.id.effect_smooth) {
                view = mSmoothBtn;
            } else if (id == R.id.effect_sharp) {
                view = mSharpBtn;
            } else if (id == R.id.effect_big_eye) {
                view = mBigEyeBtn;
            } else {
                view = mNoSelectedBtn;
            }
            if (value > 0) {
                view.setColorFilter(getContext().getResources().getColor(R.color.blue));
            } else {
                view.setColorFilter(getContext().getResources().getColor(R.color.white));
            }
        }
    }

    private static int mLastId = R.id.effect_whiten;

    @Override
    public void onClick(View v) {
        mLastId = v.getId();

        if (v == mSelectedBtn) {
            return;
        }
        if (v == mNoSelectedBtn) {
            resetEffect();
        }
        v.setBackgroundResource(R.drawable.effect_btn_selected_bg);
        mSelectedBtn.setBackgroundResource(R.drawable.effect_btn_normal_bg);
        if (mEffectItemChangedListener != null) {
            mEffectItemChangedListener.onChanged(v, mSelectedBtn);
        }
        mSelectedBtn = v;
    }

    public int getSelectedId() {
        return mLastId;
    }

    public int getEffectProgress(@IdRes int id) {
        if (sSeekBarProgressMap.containsKey(id)) {
            return sSeekBarProgressMap.get(id);
        }
        return 0;
    }

    public void resetEffect() {
        for (int key : sSeekBarProgressMap.keySet()) {
            sSeekBarProgressMap.put(key, 0);
            ((ImageView) findViewById(key)).setColorFilter(getContext().getResources().getColor(R.color.white));
        }
    }
}
