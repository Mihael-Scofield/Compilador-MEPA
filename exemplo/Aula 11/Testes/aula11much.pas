program proc2 (input, output); 
var x, y: integer;      
   procedure p(t:integer);     
   var z:integer;           
      begin                    
        if (t>1)               
           then p(1,2)
           else y:=1;          
        z:= y;                 
        y:=z*t;                
      end;                       
begin                     
   read(x);               
   p(x);       
   write (x,y)            
end. 