
Pod::Spec.new do |spec|
  spec.name         = 'BytePlusRTC'
  spec.version      = '3.42.112'
  spec.summary      = 'framework_summary'
  spec.description  = 'framework_description'
  spec.homepage     = 'https://docs.byteplus.com/byteplus-rtc/docs'
  spec.license      = { :type => 'Copyright', :text => 'Bytedance copyright' }
  spec.author       = { 'bytertc' => 'bytertc@bytedance.com' }
  spec.source       = { :path => './'}
  spec.ios.deployment_target = '9.0'
  spec.default_subspec = 'Core'
  spec.pod_target_xcconfig = { 'ENABLE_BITCODE' => 'NO'}

  spec.subspec 'Core' do |cs|
    cs.vendored_frameworks = 'BytePlusRTC.xcframework'
  end

  spec.subspec 'ScreenCapture' do |sc|
    sc.vendored_frameworks = 'BytePlusRTCScreenCapturer.xcframework'
  end
end
