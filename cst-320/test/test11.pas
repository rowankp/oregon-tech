// testing AND and OR statements
PROGRAM test11;
VAR
    a, b, c : integer;
BEGIN
    a := 1;
    b := 0;
    c := 1;

    if (a AND b)
    then WRITE(a);
    else WRITE(b); 

    if (a OR b)
    then WRITE(a);
    else WRITE(b); 

    if (a AND c)
    then WRITE(a);
    else WRITE(b); 

    if (a OR c)
    then WRITE(a);
    else WRITE(b); 
END.
