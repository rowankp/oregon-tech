// testing comparison operators and if statements
PROGRAM test9;
VAR
    a, b, c : integer;
BEGIN
    a := 1;
    b := 2;
    c := 1;

    if (a = b)
    then WRITE(a);

    if (a <= b)
    then WRITE(a);

    if (a = c)
    then WRITE(a);

    if (a >= b)
    then WRITE(a);

    if (a <> b)
    then WRITE(a);

    if (b = a)
    then WRITE(b);

    if (b <= a)
    then WRITE(b);

    if (b >= a)
    then WRITE(b);

    if (b <> a)
    then WRITE(b);
END.
