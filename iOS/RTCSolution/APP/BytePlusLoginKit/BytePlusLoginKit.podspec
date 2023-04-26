
Pod::Spec.new do |spec|
  spec.name         = 'BytePlusLoginKit'
  spec.version      = '1.0.0'
  spec.summary      = 'BytePlusLoginKit APP'
  spec.description  = 'BytePlusLoginKit App ..'
  spec.homepage     = 'https://github.com/byteplus-sdk'
  spec.license      = { :type => 'MIT', :file => 'LICENSE' }
  spec.author       = { 'author' => 'byteplus rtc' }
  spec.source       = { :path => './'}
  spec.ios.deployment_target = '9.0'
  
  spec.source_files = '**/*.{h,m,c,mm}'
  spec.resource_bundles = {
    'LoginKit' => ['Resource/*']
  }
  spec.prefix_header_contents = '#import "Masonry.h"',
                                '#import "ToolKit.h"',
                                '#import "LoginConstants.h"'
  spec.dependency 'ToolKit'
  spec.dependency 'YYModel'
  spec.dependency 'Masonry'
end
