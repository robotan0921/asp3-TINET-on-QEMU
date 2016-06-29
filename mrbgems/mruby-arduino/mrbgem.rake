MRuby::Gem::Specification.new('mruby-arduino') do |spec|
  spec.license = 'MIT'
  spec.author  = 'Minao Yamamoto'

  spec.cc.include_paths << "#{spec.dir}/src"
end
