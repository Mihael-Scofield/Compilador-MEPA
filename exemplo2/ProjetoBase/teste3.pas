program teste3 (input, output);
    var x,y: integer;
    procedure p;
        var z: integer;
        begin
            z:= x;
            x:= x-1;
            if (z>1) then 
                p;
            else 
                y:= 1;

            y:=y*z;
        end
begin
    x:= 3;
    p;
end.
