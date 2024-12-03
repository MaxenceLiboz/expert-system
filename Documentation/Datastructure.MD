# Datastructure

We must be able to get a list of rules.
It would be nice to be able to decompose each rules to just find the value step by step for example:  
```
A | B => C   
We would look for the value of A | B, let's say it is True.  
Then we know that the rules is true, therfore we need to know what make T => ? = T.  
If we check the truth table we have T => T = T.  
As a result, we know that C = True.  
```

Know, let's decompose more complexe rules.
```
A + B | (C | D) => E  
Where, A = True, B = False, C = True, D = False.  
There are parentheses, therefore we need first to do them :  
C | D = True  
We then have : A + B | True => E  
A + B = False  
We then have : False | True => E  
False | True = True  
We then have : True => E, with the rule beeing True.  
As a result, we have : T => T = T which means that E = True.
```

### Rule class
It will contain:
- The string of the rule itself
- List of calculus in order, it will take in account the parentheses, theses calculus will be pair with their values. Example :   
```
(C | D, null), (A + B | (C | D), null), ((A + B | (C | D)) => E, null) 
For each calcul in calculus:
    value = null
    oldArg = null
    while index != calcul.key().size() - 1
        value = null
        if (oldArg == null)
            arg1 = readArg() # readArg will read all parentheses if there are as one argument and get the 
                                value
        else
            arg1 = oldArg
        sign = readSign() # Will read the different sign possible can throw
        arg2 = readArg() # readArg will read all parentheses if there are as one argument and get the value
        value = calc(arg1, arg2, sign) # Gonna do a calculus depending on the sign 
        oldArg = value
    calcul.value = value

```
- A pair of the Letter/Value found

### Querry class
Will will have a solve method in it to get the value of the querry
It will contain:
- The pair Letter/Value querried
- A list of Rule that is going to be the path to find the querry

### Expert system class
It will contain:
- A list of Rule
- A list of pair Letter/Value 
- A list of Querry


