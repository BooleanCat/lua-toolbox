local buffer = require('toolbox.buffer')
local bytes = require('toolbox.bytes')

local when = describe

describe('buffer', function()
  describe('new', function()
    it('creates a buffer', function()
      assert.is_not_nil(buffer.new())
    end)

    it('has initial length 0', function()
      assert.are.equal(0, #buffer.new())
    end)

    when('initialised with a toolbox.bytes', function()
      it('has initial length of the argument', function()
        assert.are.equal(3, #buffer.new(bytes.new('foo')))
      end)
    end)

    when('called with something other than a toolbox.bytes', function()
      it('returns an error', function()
        assert.has_error(
          function() buffer.new('foo') end,
          "bad argument #1 to 'new' (toolbox.bytes expected, got string)"
        )
      end)
    end)
  end)

  describe('bytes', function()
    it('returns a copy of the buffer contents', function()
      assert.are.equal(
        bytes.new('foo'),
        buffer.new(bytes.new('foo')):bytes()
      )
    end)
  end)

  describe('__tostring', function()
    it('represents the buffer size', function()
      assert.are.equal(
        'toolbox.buffer[5]',
        string.format('%s', buffer.new(bytes.new('hello')))
      )
    end)
  end)

  describe("__tbread", function()
    it('reads bytes into a tool.bytes', function()
      local buf = buffer.new(bytes.new('hello'))
      local b = bytes.new(5)

      buf:__tbread(b)

      assert.are.equal(bytes.new("hello"), b)
    end)

    when("the destination is smaller", function()
      it('reads as much as possible into the destination', function()
        local buf = buffer.new(bytes.new('hello'))
        local b = bytes.new(3)

        assert.are.equal(3, buf:__tbread(b))
        assert.are.equal(bytes.new('hel'), b)
      end)
    end)

    when("the destination is larger", function()
      it('reads the entire buffer', function()
        local buf = buffer.new(bytes.new('hello'))
        local b = bytes.new(7)

        assert.are.equal(5, buf:__tbread(b))
        assert.are.equal(
          '[68 65 6C 6C 6F 00 00]',
          string.format('%s', b)
        )
      end)
    end)

    when('a read has already occurred', function()
      it('continues reading from where it last finished', function()
        local buf = buffer.new(bytes.new('hello'))
        local b = bytes.new(3)

        assert.are.equal(3, buf:__tbread(b))
        assert.are.equal(bytes.new('hel'), b)

        assert.are.equal(2, buf:__tbread(b))
        assert.are.equal(bytes.new('lol'), b)

        assert.are.equal(0, buf:__tbread(b))
        assert.are.equal(bytes.new('lol'), b)
      end)
    end)

    when('the buffer is exhausted', function()
      it('returns an EOF as a second argument', function()
        -- TODO: implement this next
        -- Hint: create an IO module and push a const named EOF, return this
        -- when you need to see if reading is finished.

        -- Every __tbread call should check if a second arg io.EOF was returned
        -- before attempting to read again. Future reads will always return
        -- `io.EOF`.
      end)
    end)
  end)
end)
