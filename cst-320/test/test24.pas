// testing procedure nested inside procedure
PROGRAM test24;
    PROCEDURE proc1;
    VAR
        a, b : integer;

        PROCEDURE proc2(VAR c : integer; d : integer;);
        BEGIN
            WRITE(c, d);
        END;

    BEGIN
        a := 1;
        b := 2;
        proc2(a,b);
    END;
BEGIN
    proc1;
END.
