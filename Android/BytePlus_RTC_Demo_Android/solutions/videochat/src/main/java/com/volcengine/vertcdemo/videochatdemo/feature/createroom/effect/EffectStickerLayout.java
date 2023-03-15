/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.feature.createroom.effect;

import android.content.Context;
import android.text.TextUtils;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;

import androidx.annotation.Nullable;

import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochatdemo.common.IEffectItemChangedListener;


public class EffectStickerLayout extends LinearLayout implements View.OnClickListener {
    public static final String KEY_CAIHONGZHU = "caihongzhu";
    public static final String KEY_BABY = "baby_gan";
    public static final String KEY_HEIMAOYANJING = "heimaoyanjing";
    public static final String KEY_TIANZHUGIRL = "stickers_tianzhushaonv";

    private ImageView mNoSelectedBtn;
    private ImageView mNvShengBtn;
    private ImageView mNanShengBtn;
    private ImageView mSuixingshanBtn;
    private ImageView mFuguyanjingBtn;

    private View mSelectedBtn;
    private IEffectItemChangedListener mEffectItemChangedListener;
    private String defaultSelectedStickerPath;


    public EffectStickerLayout(Context context, IEffectItemChangedListener listener, String defaultSelectedStickerPath) {
        super(context);
        this.mEffectItemChangedListener = listener;
        this.defaultSelectedStickerPath = defaultSelectedStickerPath;
        initView();
    }

    public EffectStickerLayout(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        initView();
    }

    public EffectStickerLayout(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        initView();
    }

    public void initView() {
        LayoutInflater.from(getContext()).inflate(R.layout.dialog_effect_sticker, this, true);

        mNoSelectedBtn = findViewById(R.id.no_select);
        mNoSelectedBtn.setOnClickListener(this);
        mSelectedBtn = mNoSelectedBtn;
        mNvShengBtn = findViewById(R.id.effect_shaonvmanhua);
        mNvShengBtn.setOnClickListener(this);
        mNanShengBtn = findViewById(R.id.effect_manhuanansheng);
        mNanShengBtn.setOnClickListener(this);
        mSuixingshanBtn = findViewById(R.id.effect_suixingshan);
        mSuixingshanBtn.setOnClickListener(this);
        mFuguyanjingBtn = findViewById(R.id.effect_fuguyanjing);
        mFuguyanjingBtn.setOnClickListener(this);
        if (!TextUtils.isEmpty(defaultSelectedStickerPath)) {
            setSelectedPath(defaultSelectedStickerPath);
        }
    }

    private void setSelectedPath(String path) {
        if (TextUtils.equals(path, KEY_CAIHONGZHU)) {
            updateUI(mNvShengBtn);
        } else if (TextUtils.equals(path, KEY_BABY)) {
            updateUI(mNanShengBtn);
        } else if (TextUtils.equals(path, KEY_HEIMAOYANJING)) {
            updateUI(mFuguyanjingBtn);
        } else if (TextUtils.equals(path, KEY_TIANZHUGIRL)) {
            updateUI(mSuixingshanBtn);
        } else {
            updateUI(mNoSelectedBtn);
        }
    }

    private void updateUI(View view) {
        if (view.getId() == R.id.no_select) {
            ((ImageView) view).setBackgroundResource(R.drawable.effect_btn_selected_bg);
        } else {
            ((ImageView) view).setBackgroundResource(R.drawable.effect_selected_rec_bg);
        }
        ((ImageView) mSelectedBtn).setBackgroundResource(R.drawable.effect_btn_normal_bg);
        mSelectedBtn = view;
    }

    public int getSelectedId() {
        if (mSelectedBtn != null) {
            return mSelectedBtn.getId();
        }
        return -1;
    }

    @Override
    public void onClick(View v) {
        if (v == mSelectedBtn) {
            return;
        }
        if (v.getId() == R.id.no_select) {
            ((ImageView) v).setBackgroundResource(R.drawable.effect_btn_selected_bg);
        } else {
            ((ImageView) v).setBackgroundResource(R.drawable.effect_selected_rec_bg);
        }
        ((ImageView) mSelectedBtn).setBackgroundResource(R.drawable.effect_btn_normal_bg);
        if (mEffectItemChangedListener != null) {
            mEffectItemChangedListener.onChanged(v, mSelectedBtn);
        }

        mSelectedBtn = v;
    }
}