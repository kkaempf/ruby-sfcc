%w(../ext/sfcc ../lib).each do |path|
  $LOAD_PATH.unshift(File.expand_path(File.join(File.dirname(__FILE__), path)))
end
 
require 'rubygems'
require 'openssl'
require 'sfcc'

#
# enumerate CIMOM namespaces
#
# modeled along 'EnumNamespaces' from YaWN (http://pywbem.wiki.sourceforge.net/YAWN)

puts "start"
raise unless OpenSSL::Digest::Digest.new("sha1")

puts "first sha1"

client = Sfcc::Cim::Client.connect('http://wsman:secret@localhost:5988')

puts "client #{client}"

raise unless OpenSSL::Digest::Digest.new("sha1")

puts "second sha1"

['CIM_Namespace', '__Namespace'].each do |classname|
  ['root/cimv2', 'Interop', 'interop', 'root', 'root/interop'].each do |namespace|
    op = Sfcc::Cim::ObjectPath.new(namespace, classname)
    puts "Checking #{op}"
    begin
      client.instance_names(op).each do |path|
	n = path.Name
	puts "Namespace: #{path['Name']}"
      end
    rescue Sfcc::Cim::ErrorInvalidClass, Sfcc::Cim::ErrorInvalidNamespace
    end
  end
end
