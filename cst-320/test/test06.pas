// testing binary operations with variables

PROGRAM test6;
VAR
    a, b, c : integer;
BEGIN
    a := 10;
    b := 5;

    c = a * b;
    WRITE(c);

    c = a / b;
    WRITE(c);

    c = a + b;
    WRITE(c);

    c = a - b;
    WRITE(c);

    c = a % b;
    WRITE(c);

    c = b % a;
    WRITE(c);
END. 
