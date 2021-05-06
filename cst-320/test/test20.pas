// testing multi-dimensional arrays
PROGRAM test20;
TYPE
    array1 = ARRAY [0..2] of integer;
    array2 = ARRAY [0..2, 1..3] of integer;
VAR
    a : array1;
    b : array2;
BEGIN
    a[1] := 2;
    b[2, 1] := 3;
    b[1+1, 3-1] := 4;
    
    WRITE(a[1]);
    WRITE(b[2, 1]);
    WRITE(b[2, 2]);
END.
