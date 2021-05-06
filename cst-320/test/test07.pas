// testing precedence

PROGRAM test7;
VAR
    a, b, c, d : integer;
BEGIN
    a := 1;
    b := 2;
    c := 3;
    c := 4;

    WRITE(a + b * c);
    WRITE(a - b * c);
    WRITE(c * b + a);
    WRITE(c * b - a);
    WRITE(a + b * c + d);
    WRITE(d + c * b - a);
    WRITE(c / b + a - a);
END.
