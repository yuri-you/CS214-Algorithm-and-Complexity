/*********************************************
 * OPL 12.9.0.0 Model
 * Author: 12779
 * Creation Date: 2021Äê4ÔÂ4ÈÕ at ÉÏÎç11:27:41
 *********************************************/
{string} Prod = ...;
{string} Process = ...;

int NbMonths = ...;
range Months=1..NbMonths;
float ProfitProd[Prod]=...;
float ProcessProd[Process][Prod]= ...;
int MarketProd[Months][Prod] = ...;

float CostHold = ...;
int StartHold = ...;
int EndHold = ...;
int MaxHold = ...;

int HoursMonth = ...;

int NumProcess[Process] = ...;
int NumDown[Process] = ...;
dvar int+ product[Months][Prod];
dvar int+ produce[Months][Prod];
dvar int+ sell[Months][Prod];
dvar int+ remain[Months][Prod];
dvar int+ down[Months][Process];
dvar float+ Profit;
dvar float+ Cost;
maximize Profit-Cost;
subject to{
	/*relationship constrain*/
	forall(i in Prod){
		forall(j in Months){
		  	remain[j][i]==product[j][i]-sell[j][i];
  		 }		  	
	}
	forall(i in Months){
		forall(j in Prod){
			sell[i][j]<=MarketProd[i][j];		
		}	
	}
	forall(i in Months){
		forall(j in Prod){
			if(i==1){
				product[i][j]==produce[i][j]+StartHold;			
			}		
			else{
				product[i][j]==produce[i][j]+remain[i-1][j];	
			}
		}	
	}
	
	/*machine down constrain*/
	forall(j in Process){
		sum(i in Months)down[i][j] == NumDown[j];
	}
	
	/*produce machine constarin */
	forall(i in Months){
		forall(j in Process){
			sum(k in Prod)(produce[i][k]*ProcessProd[j][k])<=HoursMonth*(NumProcess[j]-down[i][j]);
		}
	}
	/*store constrain*/
	forall(i in Months){
		forall(j in Prod){
			if(i==NbMonths){
				remain[i][j]==EndHold;		
			}	
			else{
				remain[i][j]<=MaxHold;			
			}
		}
	}
	Profit == sum(i in Months) sum(j in Prod)sell[i][j]*ProfitProd[j];
	Cost == sum(i in 1..NbMonths)sum(j in Prod)remain[i][j]*CostHold;
}
execute {
	if (cplex.getCplexStatus() == 1) {
    	writeln('selling profit = ', Profit)
    	writeln('holding cost of = ', Cost)
    	writeln('net  profit = ', Profit-Cost)
		for(i in Months){
			write('In Months',i)		
			write(':\n')
			for(j in Prod)	{
				write("sell ",sell[i][j])
				write(" ",j)
				write("   ")	
  			}
  			write("\n")		
  			for(j in Prod)	{
				write("hole ",remain[i][j])
				write(" ",j)
				write("   ")	
  			}
  			write("\n")		
  			for(j in Prod)	{
				write("make ",produce[i][j])
				write(" ",j)
				write("   ")	
  			}
  			write("\n")	
  			write("number of maintenance machines of ")
  			for(j in Process)	{
				write(j)
				write(" : ",down[i][j])
				write("    ")
  			}
  			write("\n")					
		}
	}
}