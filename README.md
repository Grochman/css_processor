# CSS procesor
The CSS Processor is a C++ program that processes CSS code and executes specific commands to retrieve information about the CSS blocks, selectors, and attributes.
## Available commands: 
- `????`: start command section
- `****`: end command section
- `?`: get number of css blocks
- `i,S,?`: get number of selectors in i block
- `i,A,?`: get number of attributes in i block
- `i,S,j`: get j selector from i block
- `i,A,n`: get from i block value for attribute n
- `n,A,?`: get number of blocks that contain n attribute
- `z,S,?`: get number of z selector occurrences
- `z,E,n`: get value of attribute n for selector z
- `i,D,*`: delete i block
- `i,D,n`: delete from i block attribute n

The CSS Processor takes these commands as input and provides corresponding output values for each command. 
## Example:
#breadcrumb 
{ 
	width: 80%; 
	font-size: 9pt; 
} 

h1, body { 
	min-width: 780px; 
	margin: 0; 
	padding: 0; 
	font-family: "Trebuchet MS", "Lucida Grande", Arial; 
	font-size: 85%; 
	color: #666666; 
} 

h1, h2, h3, h4, h5, h6 {color: #0066CB;} 
???? 
? 
1,S,? 
1,S,1 
1,A,? 
2,A,font-family 
h1,S,? 
color,A,? 
h1,E,color 
1,A,padding 
1,D,* 
? 
2,D,color 
? 

**** 
h1, h2, h3, h4, h5, h6 {color: #0066FF;} 
???? 
? 
## Result:
? == 3 
1,S,? == 1 
1,S,1 == #breadcrumb 
1,A,? == 2 
2,A,font-family == "Trebuchet MS", "Lucida Grande", Arial 
h1,S,? == 2 
color,A,? == 2 
h1,E,color == #0066CB 
1,D,* == deleted 
? == 2 
2,D, color == deleted 
? == 1 
? == 2 
