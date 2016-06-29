MRuby::Gem::Specification.new('gr_sakura') do |spec|
  spec.license = 'TOPPERS License'
  spec.author  = 'Cores Co., Ltd.'
  spec.summary = 'GR-SAKURA mruby-arduino target depends'

  spec.cc.include_paths << "#{spec.dir}/src"
end
