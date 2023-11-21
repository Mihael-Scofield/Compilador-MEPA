program DummyAninhado (input, output);
var a:  integer;
   function g(t : integer):integer;
   begin
      g:=t+1
   end;
begin
   a:= g(g(g(1)));
end.
   