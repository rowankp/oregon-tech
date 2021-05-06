// testing array declarations with expressions
PROGRAM test13;
TYPE
    array1 = ARRAY [0..2] of integer;
VAR
    a : array1;
BEGIN
    a[0 * 1] := 0;
    a[2 - 1] := 1;
    a[1 + 1] := 2;

    WRITE(a[0]);
    WRITE(a[1]);
    WRITE(a[2]);
END.
