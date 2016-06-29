MRuby::Gem::Specification.new('gr_peach') do |spec|
  spec.license = 'TOPPERS License'
  spec.author  = 'Cores Co., Ltd.'
  spec.summary = 'GR-PEACH mruby-arduino target depends'

  spec.cc.include_paths << "#{spec.dir}/src"
end
