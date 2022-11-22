
Pod::Spec.new do |spec|
  spec.name         = 'Core'
  spec.version      = '1.0.0'
  spec.summary      = 'Core'
  spec.description  = 'Core ...'
  spec.homepage     = 'https://github.com/byteplus-sdk'
  spec.license      = { :type => 'MIT', :file => 'LICENSE' }
  spec.author       = { 'author' => 'byteplus rtc' }
  spec.source       = { :path => './'}
  spec.ios.deployment_target = '9.0'
  
  spec.prefix_header_contents = '#import "Constants.h"'
  
  spec.source_files = '**/*.{h,m}'
  spec.resource_bundles = {
    'Core' => ['Resource/*']
  }
  spec.dependency 'Masonry'
  spec.dependency 'YYModel'
  spec.dependency 'AFNetworking'
  spec.dependency 'BytePlusRTC'
end
