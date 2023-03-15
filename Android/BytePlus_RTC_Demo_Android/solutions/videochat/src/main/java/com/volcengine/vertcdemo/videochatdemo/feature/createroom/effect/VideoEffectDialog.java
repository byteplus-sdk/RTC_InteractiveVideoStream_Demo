/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.feature.createroom.effect;

import android.content.Context;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.Gravity;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.SeekBar;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.viewpager.widget.ViewPager;

import com.google.android.material.tabs.TabLayout;
import com.volcengine.vertcdemo.common.BaseDialog;
import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochatdemo.common.IEffectItemChangedListener;
import com.volcengine.vertcdemo.videochatdemo.common.VideoChatEffectBeautyLayout;
import com.volcengine.vertcdemo.videochatdemo.core.VideoChatRTCManager;

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map;

public class VideoEffectDialog extends BaseDialog implements IEffectItemChangedListener {

    private TabLayout mTabLayout;
    private ViewPager mViewPager;
    private SeekBar mSeekbar;
    private View mEffectSeekbarArea;
    private TextView mStrengthNum;
    private VideoChatEffectBeautyLayout mBeautyLayout;
    private EffectFilterLayout mFilterLayout;
    private EffectStickerLayout mStickerLayout;
    private Context mContext;

    private final String mExternalResourcePath;
    public static final Integer[] TAB_NAMES = {R.string.beautify_text, R.string.filter_text, R.string.sticker_text};

    private static final String FILTER_NAIYOU = "Filter_02_14";
    private static final String FILTER_OX = "Filter_03_20";
    private static final String FILTER_MITAO = "Filter_06_03";
    private static final String FILTER_LIANAI = "Filter_35_L3";

    private final ArrayList<String> mEffectPathList = new ArrayList<>();

    public VideoEffectDialog(@NonNull Context context) {
        super(context);
        mContext = context;
        mExternalResourcePath = context.getExternalFilesDir("assets").getAbsolutePath();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.effect_dialog_layout);
        Window window = getWindow();
        window.setBackgroundDrawableResource(android.R.color.transparent);
        window.setLayout(WindowManager.LayoutParams.MATCH_PARENT, WindowManager.LayoutParams.WRAP_CONTENT);
        window.setGravity(Gravity.BOTTOM);
        window.setDimAmount(0);
        initUI();
    }

    public void initUI() {
        mViewPager = findViewById(R.id.effect_vp);
        TabViewPageAdapter adapter = new TabViewPageAdapter(getContext(), Arrays.asList(TAB_NAMES), generateTabViews());
        mViewPager.setAdapter(adapter);

        mTabLayout = findViewById(R.id.effect_tab);
        mTabLayout.setupWithViewPager(mViewPager);
        mTabLayout.addOnTabSelectedListener(new TabLayout.OnTabSelectedListener() {
            @Override
            public void onTabSelected(TabLayout.Tab tab) {

                if (TextUtils.equals(tab.getText(), mContext.getString(R.string.sticker_text))) {
                    mSeekbar.setVisibility(View.GONE);
                    mEffectSeekbarArea.setVisibility(View.GONE);
                } else if (TextUtils.equals(tab.getText(), mContext.getString(R.string.beautify_text))) {
                    mSeekbar.setProgress(mBeautyLayout.getEffectProgress(mBeautyLayout.getSelectedId()));
                    mSeekbar.setVisibility(mBeautyLayout.getSelectedId() == R.id.no_select ? View.GONE : View.VISIBLE);
                    mEffectSeekbarArea.setVisibility(mBeautyLayout.getSelectedId() == R.id.no_select ? View.GONE : View.VISIBLE);
                } else if (TextUtils.equals(tab.getText(), mContext.getString(R.string.filter_text))) {
                    mSeekbar.setProgress(mFilterLayout.getEffectProgress(mFilterLayout.getSelectedId()));
                    mSeekbar.setVisibility(mFilterLayout.getSelectedId() == R.id.no_select ? View.GONE : View.VISIBLE);
                    mEffectSeekbarArea.setVisibility(mFilterLayout.getSelectedId() == R.id.no_select ? View.GONE : View.VISIBLE);
                }
            }

            @Override
            public void onTabUnselected(TabLayout.Tab tab) {

            }

            @Override
            public void onTabReselected(TabLayout.Tab tab) {

            }
        });

        mEffectSeekbarArea = findViewById(R.id.effect_seekbar_area);
        mSeekbar = findViewById(R.id.effect_seekbar);
        mStrengthNum = findViewById(R.id.strength_num);
        mSeekbar.setVisibility(mBeautyLayout.getSelectedId() == R.id.no_select ? View.GONE : View.VISIBLE);
        mEffectSeekbarArea.setVisibility(mBeautyLayout.getSelectedId() == R.id.no_select ? View.GONE : View.VISIBLE);
        int currentProgress = mBeautyLayout.getEffectProgress(mBeautyLayout.getSelectedId());
        mSeekbar.setProgress(currentProgress);
        mStrengthNum.setText(String.valueOf(currentProgress));

        mSeekbar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            int viewId = -1;

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if (!fromUser) {
                    return;
                }
                float value = seekBar.getProgress() / 100f;
                mStrengthNum.setText(String.valueOf(progress));
                View currentView = adapter.getPrimaryItem();
                int tabPos = mTabLayout.getSelectedTabPosition();
                if (tabPos == 0) {
                    VideoChatEffectBeautyLayout effectBeautyLayout = (VideoChatEffectBeautyLayout) currentView;
                    viewId = effectBeautyLayout.getSelectedId();
                    if (viewId == R.id.effect_whiten) {
                        VideoChatRTCManager.ins().updateVideoEffectNode(getByteComposePath(), "whiten", value);
                    } else if (viewId == R.id.effect_smooth) {
                        VideoChatRTCManager.ins().updateVideoEffectNode(getByteComposePath(), "smooth", value);
                    } else if (viewId == R.id.effect_big_eye) {
                        VideoChatRTCManager.ins().updateVideoEffectNode(getByteShapePath(), "Internal_Deform_Eye", value);
                    } else if (viewId == R.id.effect_sharp) {
                        VideoChatRTCManager.ins().updateVideoEffectNode(getByteShapePath(), "Internal_Deform_Overall", value);
                    }
                } else if (tabPos == 1) {
                    viewId = ((EffectFilterLayout) currentView).getSelectedId();
                    if (viewId == R.id.effect_landiao) {
                        VideoChatRTCManager.ins().setVideoEffectColorFilter(getByteColorFilterPath() + FILTER_NAIYOU);
                    } else if (viewId == R.id.effect_lengyang) {
                        VideoChatRTCManager.ins().setVideoEffectColorFilter(getByteColorFilterPath() + FILTER_OX);
                    } else if (viewId == R.id.effect_lianai) {
                        VideoChatRTCManager.ins().setVideoEffectColorFilter(getByteColorFilterPath() + FILTER_LIANAI);
                    } else if (viewId == R.id.effect_yese) {
                        VideoChatRTCManager.ins().setVideoEffectColorFilter(getByteColorFilterPath() + FILTER_MITAO);
                    }
                    VideoChatRTCManager.ins().updateColorFilterIntensity(viewId == R.id.no_select ? 0 : value);
                }
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                int tabPos = mTabLayout.getSelectedTabPosition();
                if (tabPos == 0) {
                    VideoChatEffectBeautyLayout.sSeekBarProgressMap.put(viewId, seekBar.getProgress());
                } else if (tabPos == 1) {
                    EffectFilterLayout.sSeekBarProgressMap.clear();
                    EffectFilterLayout.sSeekBarProgressMap.put(viewId, seekBar.getProgress());
                }
            }
        });
    }

    public List<View> generateTabViews() {
        List<View> mViews = new ArrayList<>();
        for (int tabName : TAB_NAMES) {
            if (tabName == R.string.beautify_text) {
                mViews.add(mBeautyLayout = new VideoChatEffectBeautyLayout(getContext(), this));
            } else if (tabName == R.string.filter_text) {
                mViews.add(mFilterLayout = new EffectFilterLayout(getContext(), this));
            } else if (tabName == R.string.sticker_text) {
                mStickerLayout = new EffectStickerLayout(getContext(), this, VideoChatRTCManager.ins().getStickerPath());
                mViews.add(mStickerLayout);
            }
        }
        return mViews;
    }

    public String getByteStickerPath() {
        File stickerPath = new File(mExternalResourcePath + "/resource/", "cvlab/StickerResource.bundle");
        return stickerPath.getAbsolutePath() + "/";
    }

    public String getByteComposePath() {
        File composerPath = new File(mExternalResourcePath + "/resource/", "cvlab/ComposeMakeup.bundle");
        return composerPath.getAbsolutePath() + "/ComposeMakeup/beauty_Android_live";
    }

    public String getByteShapePath() {
        File composerPath = new File(mExternalResourcePath + "/resource/", "cvlab/ComposeMakeup.bundle");
        return composerPath.getAbsolutePath() + "/ComposeMakeup/reshape_live";
    }

    public String getByteColorFilterPath() {
        File filterPath = new File(mExternalResourcePath + "/resource/", "cvlab/FilterResource.bundle");
        return filterPath.getAbsolutePath() + "/Filter/";
    }


    @Override
    public void onChanged(View newItem, View lastItem) {
        if (newItem.getId() == R.id.no_select) {
            mSeekbar.setVisibility(View.GONE);
            mEffectSeekbarArea.setVisibility(View.GONE);
        } else if (mTabLayout.getSelectedTabPosition() != 2) {
            mSeekbar.setVisibility(View.VISIBLE);
            mEffectSeekbarArea.setVisibility(View.VISIBLE);
        }

        if (mTabLayout.getSelectedTabPosition() == 0) {
            int currentProgress = mBeautyLayout.getEffectProgress(newItem.getId());
            mSeekbar.setProgress(currentProgress);
            mStrengthNum.setText(String.valueOf(currentProgress));

            VideoChatEffectBeautyLayout.sSeekBarProgressMap.put(newItem.getId(), currentProgress);
            mBeautyLayout.updateStatusByValue();
            if (newItem.getId() == R.id.no_select) {
                VideoChatRTCManager.ins().updateVideoEffectNode(getByteComposePath(), "whiten", 0);
                VideoChatRTCManager.ins().updateVideoEffectNode(getByteComposePath(), "smooth", 0);
                VideoChatRTCManager.ins().updateVideoEffectNode(getByteShapePath(), "Internal_Deform_Eye", 0);
                VideoChatRTCManager.ins().updateVideoEffectNode(getByteShapePath(), "Internal_Deform_Overall", 0);
            } else {
                // 选中非清空效果不影响。可调用一次接口
                for (Map.Entry<Integer, Integer> entry : VideoChatEffectBeautyLayout.sSeekBarProgressMap.entrySet()) {

                    float value = entry.getValue() == null ? 0 : entry.getValue();
                    int id = entry.getKey();
                    if (id == R.id.effect_whiten) {
                        VideoChatRTCManager.ins().updateVideoEffectNode(getByteComposePath(), "whiten", value / 100);
                    } else if (id == R.id.effect_smooth) {
                        VideoChatRTCManager.ins().updateVideoEffectNode(getByteComposePath(), "smooth", value / 100);
                    } else if (id == R.id.effect_big_eye) {
                        VideoChatRTCManager.ins().updateVideoEffectNode(getByteShapePath(), "Internal_Deform_Eye", value / 100);
                    } else if (id == R.id.effect_sharp) {
                        VideoChatRTCManager.ins().updateVideoEffectNode(getByteShapePath(), "Internal_Deform_Overall", value / 100);
                    }
                }
            }
        } else if (mTabLayout.getSelectedTabPosition() == 1) {
            int currentProgress = mFilterLayout.getEffectProgress(newItem.getId());
            mSeekbar.setProgress(currentProgress);
            mStrengthNum.setText(String.valueOf(currentProgress));
            for (Map.Entry<Integer, Integer> entry : EffectFilterLayout.sSeekBarProgressMap.entrySet()) {
                if (entry.getKey() != newItem.getId()) {
                    entry.setValue(0);
                }
            }

            if (newItem.getId() == R.id.effect_landiao) {
                VideoChatRTCManager.ins().setVideoEffectColorFilter(getByteColorFilterPath() + FILTER_NAIYOU);
            } else if (newItem.getId() == R.id.effect_lengyang) {
                VideoChatRTCManager.ins().setVideoEffectColorFilter(getByteColorFilterPath() + FILTER_OX);
            } else if (newItem.getId() == R.id.effect_lianai) {
                VideoChatRTCManager.ins().setVideoEffectColorFilter(getByteColorFilterPath() + FILTER_MITAO);
            } else if (newItem.getId() == R.id.effect_yese) {
                VideoChatRTCManager.ins().setVideoEffectColorFilter(getByteColorFilterPath() + FILTER_LIANAI);
            }
            VideoChatRTCManager.ins().updateColorFilterIntensity((float) currentProgress / 100);
        } else if (mTabLayout.getSelectedTabPosition() == 2) {
            int id = newItem.getId();
            if (id == R.id.effect_manhuanansheng) {
                VideoChatRTCManager.ins().setStickerNodes(EffectStickerLayout.KEY_BABY);
            } else if (id == R.id.effect_shaonvmanhua) {
                VideoChatRTCManager.ins().setStickerNodes(EffectStickerLayout.KEY_CAIHONGZHU);
            } else if (id == R.id.effect_suixingshan) {
                VideoChatRTCManager.ins().setStickerNodes(EffectStickerLayout.KEY_TIANZHUGIRL);
            } else if (id == R.id.effect_fuguyanjing) {
                VideoChatRTCManager.ins().setStickerNodes(EffectStickerLayout.KEY_HEIMAOYANJING);
            } else if (id == R.id.no_select) {
                VideoChatRTCManager.ins().setStickerNodes("");
            }
        }
    }
}
