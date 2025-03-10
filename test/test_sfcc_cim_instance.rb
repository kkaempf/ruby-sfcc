require_relative 'helper'

describe 'object path for CIM_ComputerSystem and running CIMOM' do
  include SfccTestUtils

  before do
    setup_cim_client
    @op_computer_system = Sfcc::Cim::ObjectPath.new('root/cimv2', 'CIM_ComputerSystem')
  end

  it 'should be running' do
    assert cimom_running?
  end

  it 'should be able to create an instance' do
    instance = Sfcc::Cim::Instance.new(@op_computer_system)
    assert instance
  end
end

describe 'an instance of CIM_ComputerSystem' do
  include SfccTestUtils

  before do
    setup_cim_client
    op = Sfcc::Cim::ObjectPath.new('root/cimv2')
    @instance = @client.query(op, 'select * from CIM_ComputerSystem', 'wql').to_a.first
  end

  it 'should be running' do
    assert cimom_running?
  end

  it 'should respond to property Name' do
    assert_kind_of(String, @instance.property('Name'))
  end

  it 'should be able to iterate over properties' do
    count = 0
    @instance.each_property do |name, _value|
      count += 1
      assert name
      # value can be nil
    end
    assert count > 0
  end

  it 'should be able to set and retrieve stringproperties' do
    assert_raises Sfcc::Cim::ErrorNoSuchProperty do
      @instance.property('foobar')
    end
    @instance.set_property('Name', 'newname')
    assert_equal 'newname', @instance.property('Name')
  end

  it 'should be able to enumerate qualifiers' do
    @instance.each_qualifier do |k, _v|
      refute_nil(k)
    end

    qualifiers = @instance.qualifiers
    assert qualifiers.empty?
    assert_equal qualifiers.size, @instance.qualifier_count
  end

  it 'should be able to enumerate qualifiers for a property' do
    @instance.each_property_qualifier('Status') do |k, _v|
      refute_nil(k)
    end

    qualifiers = @instance.property_qualifiers('Status')
    assert qualifiers.empty?
    assert_equal qualifiers.size, @instance.qualifier_count
  end
end
