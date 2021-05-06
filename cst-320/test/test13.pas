// testing array declarations
PROGRAM test13;
TYPE
    array1 = ARRAY [0..2] of integer;
    array2 = ARRAY [3..5] of integer;
VAR
    a : array1;
    b : array2;
BEGIN
    a[0] := 0;
    a[1] := 1;
    a[2] := 2;

    WRITE(a[0]);
    WRITE(a[1]);
    WRITE(a[2]);

    b[3] := 3;
    b[4] := 4;
    b[5] := 5;

    WRITE(b[3]);
    WRITE(b[4]);
    WRITE(b[5]);
END.
