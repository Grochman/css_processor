# css_procesor
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
