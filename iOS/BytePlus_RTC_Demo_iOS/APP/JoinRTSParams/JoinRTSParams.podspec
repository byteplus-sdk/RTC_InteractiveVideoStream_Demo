
Pod::Spec.new do |spec|
  spec.name         = 'JoinRTSParams'
  spec.version      = '1.0.0'
  spec.summary      = 'JoinRTSParams APP'
  spec.description  = 'JoinRTSParams App ..'
  spec.homepage     = 'https://github.com/byteplus-sdk'
  spec.license      = { :type => 'MIT', :file => 'LICENSE' }
  spec.author       = { 'author' => 'byteplus rtc' }
  spec.source       = { :path => './'}
  spec.ios.deployment_target = '9.0'
  
  spec.source_files = '**/*.{h,m,c,mm}'
  spec.prefix_header_contents = '#import "Core.h"'
  spec.dependency 'Core'
  spec.dependency 'YYModel'
end
