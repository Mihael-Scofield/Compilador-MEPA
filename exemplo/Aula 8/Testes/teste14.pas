program varsGlobais (input, output);
var a,b,c,d : integer;
begin
    a:= 9;
    b:= 9;
    while (a=b) do 
    begin
        c:= 8;
        d:= 8;
        while (c=d) do 
        begin
            c:=1;
        end;
        b:=1;
    end;
end.

