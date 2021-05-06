// testing comparison operators and if else statements
PROGRAM test10;
VAR
    a, b, c : integer;
BEGIN
    a := 1;
    b := 2;
    c := 1;

    if (a = b)
    then WRITE(a);
    else WRITE(b); 

    if (a <= b)
    then WRITE(a);
    else WRITE(b); 

    if (a = c)
    then WRITE(a);
    else WRITE(b); 

    if (a >= b)
    then WRITE(a);
    else WRITE(b); 

    if (a <> b)
    then WRITE(a);
    else WRITE(b);

    if (b = a)
    then WRITE(b);
    else WRITE(a);

    if (b <= a)
    then WRITE(b);
    else WRITE(a);

    if (b >= a)
    then WRITE(b);
    else WRITE(a); 

    if (b <> a)
    then WRITE(b);
    else WRITE(a);
END.
