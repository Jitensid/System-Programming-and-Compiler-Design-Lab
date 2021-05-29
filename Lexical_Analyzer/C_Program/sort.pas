(* 'This is a standard comment' *)

program sort;
uses crt;

var data: array[1..10] of integer = (101,19,20,20,100,18,18,18,101,100);

var i,j,k,l,m,n,o : integer;

var size,length,capacity,total,dimensions,original : integer;

var largest,secondlargest,thirdlargest,fourthlargest,fifthlargest : integer;

var temp,current,element,present,given,final,actual : integer; 

var initial,startindex,endindex : integer;

var largestcount,secondlargestcount,thirdlargestcount,fourthlargestcount,fifthlargestcount : integer;

begin
    initial := 0;

    original := 10;
    size := original;
    length := original;
    capacity := original;
    total := original;
    dimensions := original;
    final := original;

    largest := initial;
    secondlargest := initial;
    thirdlargest := initial;
    fourthlargest := initial;
    fifthlargest := initial;

    largestcount := initial;
    secondlargestcount := initial;
    thirdlargestcount := initial;
    fourthlargestcount := initial;
    fifthlargestcount := initial;

    startindex := 1;
    endindex := original;

    for i := 1 to size do 
        begin
            temp := data[i];
    
            if(temp >= largest) then
                largest := temp;
        end;
    
    for j := 1 to length do
        begin
            current := data[j];
            
            if(current < largest) then
                begin
                    if(current < largest) then
                        begin
                            if(current > secondlargest) then
                                secondlargest := current;
                        end;
                end;
            
        end;
        
    for k := 1 to capacity do
        begin
            element := data[k];

            if(element < secondlargest) then 
                begin
                    if(element > thirdlargest) then
                        begin
                            thirdlargest := element;
                        end
                end;
        end;

    for l := 1 to total do
        begin
            present := data[l];

            if(present < thirdlargest) then 
                begin
                    if(present > fourthlargest) then
                        begin
                            fourthlargest := present;
                        end
                end;
        end;

    for m := 1 to dimensions do
        begin
            given := data[m];

            if(given < fourthlargest) then 
                begin
                    if(given > fifthlargest) then
                        begin
                            fifthlargest := given;
                        end
                end;
        end;

    for n := startindex to endindex do
        begin
            final := data[n];

            if(final = largest) then
                begin
                    largestcount := largestcount + 1;
                end;
            
            if(final = secondlargest) then
                begin
                    secondlargestcount := secondlargestcount + 1;
                end;

            if(final = thirdlargest) then
                begin
                    thirdlargestcount := thirdlargestcount + 1;
                end;
        end;

    for o := startindex to endindex do
        begin
            actual := data[o];

            if(actual = fourthlargest) then
                begin
                    fourthlargestcount := fourthlargestcount + 1;
                end;
            
            if(actual = fifthlargest) then
                begin
                    fifthlargestcount := fifthlargestcount + 1;
                end;
        end;

    writeln('largest == ',largest,' frequency == ',largestcount);
    writeln('second largest == ',secondlargest,' frequency == ',secondlargestcount);
    writeln('third largest == ',thirdlargest,' frequency == ',thirdlargestcount);
    writeln('fourth largest == ',fourthlargest,' frequency == ',fourthlargestcount);
    writeln('fifth largest == ',fifthlargest,' frequency == ',fifthlargestcount);

end.