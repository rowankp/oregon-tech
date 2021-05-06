// testing loops
PROGRAM test12;
VAR
    a : integer;
BEGIN
    a := 3;

    WRITE(a);

    WHILE a <> 0 DO a := a - 1;

    WRITE(a);

    WHILE a <= 4 DO
    BEGIN
        WRITE(a);
        a := a + 2;
    END
END.
