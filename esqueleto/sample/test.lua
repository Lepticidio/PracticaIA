MOAISim.openWindow("game", 1024, 768)

viewport = MOAIViewport.new()
viewport:setSize (1024, 768)
viewport:setScale (1024, -768)

layer = MOAILayer2D.new()
layer:setViewport(viewport)
MOAISim.pushRenderPass(layer)
--[[
--Texture of enemy character
texture_name = "mago.png"
gfxQuad = MOAIGfxQuad2D.new()
gfxQuad:setTexture(texture_name)
char_size = 32
gfxQuad:setRect(-char_size/2, -char_size/2, char_size/2, char_size/2)
gfxQuad:setUVRect(0, 0, 1, 1)

prop = MOAIProp2D.new()
prop:setDeck(gfxQuad)

enemy = Character.new()
-- Add prop to be the renderable for this character
enemy:setProp(prop, layer)
enemy:checkIsEnemy(true)
-- Start the character (allow calls to OnUpdate)
enemy:start()
enemy:setLoc(-500, 0)
enemy:setRot(0)
enemy:setLinearVel(100, 0)
--entity:setAngularVel(30)

--Texture of player character
texture_name = "ghost32.png"
gfxQuad = MOAIGfxQuad2D.new()
gfxQuad:setTexture(texture_name)
char_size = 32
gfxQuad:setRect(-char_size/2, -char_size/2, char_size/2, char_size/2)
gfxQuad:setUVRect(0, 0, 1, 1)

prop = MOAIProp2D.new()
prop:setDeck(gfxQuad)

entity = Character.new()
-- Add prop to be the renderable for this character
entity:setProp(prop, layer)
entity:checkIsEnemy(false, enemy);
-- Start the character (allow calls to OnUpdate)
entity:start()
entity:setLoc(0, 0)
entity:setRot(0)
entity:setLinearVel(100, 0)
--entity:setAngularVel(30)
]]

--Texture of player character
texture_name = "dragon.png"
gfxQuad = MOAIGfxQuad2D.new()
gfxQuad:setTexture(texture_name)
char_size = 64
gfxQuad:setRect(-char_size/2, -char_size/2, char_size/2, char_size/2)
gfxQuad:setUVRect(0, 0, 1, 1)

prop = MOAIProp2D.new()
prop:setDeck(gfxQuad)

entity = Character.new()
-- Add prop to be the renderable for this character
entity:setProp(prop, layer)
entity:checkIsEnemy(false, enemy);
-- Start the character (allow calls to OnUpdate)
entity:start()
entity:setLoc(-300, -100)
entity:setRot(0)
entity:setLinearVel(0, 0)
--entity:setAngularVel(30)


-- Enable Debug Draw
debug = MOAIDrawDebug.get();
layer:setDrawDebug(debug)
-- Add this character to draw debug
MOAIDrawDebug.insertEntity(entity)
--MOAIDrawDebug.insertEntity(enemy);

mouseX = 0
mouseY = 0

function onClick(down)
  enemy:setLoc(mouseX, mouseY)
  entity:setRot(0)
end

function pointerCallback(x, y)
    mouseX, mouseY = layer:wndToWorld(x, y)
end

MOAIInputMgr.device.mouseLeft:setCallback(onClick)
MOAIInputMgr.device.pointer:setCallback(pointerCallback)
