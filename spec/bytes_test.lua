local bytes = require('toolbox.bytes')

describe("bytes", function()
  it("can be initialised", function()
    assert.is_not_nil(bytes.new())
  end)

  it("has initial length 0", function()
    assert.are.equal(#bytes.new(), 0)
  end)
end)
