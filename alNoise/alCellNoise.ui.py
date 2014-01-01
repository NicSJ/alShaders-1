import uigen

ui.shader({
	'name':'alCellNoise',
	'description':'Cell noise pattern generator',
	'output':'rgb',
	'maya_name':'alCellNoise',
	'maya_classification':'texture',
	'maya_id':'0x00116408',
	'maya_swatch':True,
	'maya_matte':False,
	'maya_bump':False,
	'soft_name':'ALS_CellNoise',
	'soft_classification':'texture',
	'soft_version':1
})

ui.parameter('space', 'enum', 'world',  'Space', enum_names=[
	"world",
	"object",
	"Pref",
	"UV"
])
ui.parameter('frequency', 'float', 1.0 ,'Frequency', connectible=False)
ui.parameter('mode', 'enum', 'features', 'Mode', enum_names=[
	"features",
	"chips"
])

with uigen.group(ui, 'Features', False):
	ui.parameter('octaves', 'int', 1, 'Octaves', connectible=False)
	ui.parameter('lacunarity', 'int', 2.121, 'Lacunarity', connectible=False)
	ui.parameter('randomness', 'int', 1.0, 'Randomness', connectible=False)

	with uigen.group(ui, 'Feature weights', False):
		ui.parameter('f1w', 'float', -1.0, 'F1')
		ui.parameter('f2w', 'float', 1.0, 'F2')
		ui.parameter('f3w', 'float', 0.0, 'F3')
		ui.parameter('f4w', 'float', 0.0, 'F4')
		ui.parameter('mynkowskiShape', 'float', 2.0, 'Shape')

		uigen.remapControls(ui)

		ui.parameter('color1', 'rgb', (0.0, 0.0, 0.0), 'Color 1')
		ui.parameter('color2', 'rgb', (0.0, 0.0, 0.0), 'Color 2')

with uigen.group(ui, 'Chips', False):
	ui.parameter('smoothChips', 'bool', False, 'Smooth chips')
	ui.parameter('chipColor1', 'rgb', (.383, .318, .252), 'Chip color 1')
	ui.parameter('chipProb1', 'float', 0.2, 'Chip probability 1')
	ui.parameter('chipColor2', 'rgb', (.383, .191, .01), 'Chip color 2')
	ui.parameter('chipProb2', 'float', 0.4, 'Chip probability 2')
	ui.parameter('chipColor3', 'rgb', (.635, .612, .563), 'Chip color 3')
	ui.parameter('chipProb3', 'float', 0.6, 'Chip probability 3')
	ui.parameter('chipColor4', 'rgb', (.509, .361, .213), 'Chip color 4')
	ui.parameter('chipProb4', 'float', 0.8, 'Chip probability 4')
	ui.parameter('chipColor5', 'rgb', (.593, .472, .248), 'Chip color 5')
	ui.parameter('chipProb5', 'float', 1.0, 'Chip probability 5')

ui.parameter('P', 'vector', (0.0, 0.0, 0.0), 'P')
