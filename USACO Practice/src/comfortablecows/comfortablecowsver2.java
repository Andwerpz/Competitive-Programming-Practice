
package comfortablecows;

import java.io.*;
import java.util.*;

public class comfortablecowsver2 {
	
	static int[] addTempCow(int[] coords, Cow[][] cows) {
		
		int x = coords[0];
		int y = coords[1];
		
		x -= 1;
    	
    	if(x >= 0 && cows[x][y] == null) {
    		cows[x][y] = new Cow(true, 0);
    		return new int[] {x, y};
    	}
    	
    	x += 2;
    	
    	if(x < cows.length && cows[x][y] == null) {
    		cows[x][y] = new Cow(true, 0);
    		return new int[] {x, y};
    	}
    	
    	x -= 1;
    	y -= 1;
    	
    	if(y >= 0 && cows[x][y] == null) {
    		cows[x][y] = new Cow(true, 0);
    		return new int[] {x, y};
    	}
    	
    	y += 2;
    	
    	if(y < cows.length && cows[x][y] == null) {
    		cows[x][y] = new Cow(true, 0);
    		return new int[] {x, y};
    	}
    	
    	return new int[] {0, 0};
		
	}
	
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    Cow[][] cows = new Cow[2500][2500];
    
    StringBuilder fout = new StringBuilder();
    int numTemp = 0;
    
    for(int i = 0; i < n; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int a = Integer.parseInt(st.nextToken()) + 1000;
    	int b = Integer.parseInt(st.nextToken()) + 1000;
    	
    	if(cows[a][b] != null) {	//permanent cow coordinates are always unique
    		numTemp --;
    	}
    	
    	cows[a][b] = new Cow(false, 0);
    	
    	Stack<int[]> toProcess = new Stack<int[]>();
    	toProcess.add(new int[] {a, b});
    	
    	
    	
    	while(toProcess.size() != 0) {
    		
    		int[] cur = toProcess.pop();
    		
    		int x = cur[0];
    		int y = cur[1];
    		
	    	x -= 1;
	    	
	    	if(x >= 0 && cows[x][y] != null) {
	    		cows[cur[0]][cur[1]].adj++;
	    		cows[x][y].adj++;
	    		if(cows[x][y].adj == 3) {
	    			toProcess.add(addTempCow(new int[] {x, y}, cows));
	    			numTemp ++;
	    		}
	    	}
	    	
	    	x += 2;
	    	
	    	if(x < cows.length && cows[x][y] != null) {
	    		cows[cur[0]][cur[1]].adj++;
	    		cows[x][y].adj++;
	    		if(cows[x][y].adj == 3) {
	    			toProcess.add(addTempCow(new int[] {x, y}, cows));
	    			numTemp ++;
	    		}
	    	}
	    	
	    	x -= 1;
	    	y -= 1;
	    	
	    	if(y >= 0 && cows[x][y] != null) {
	    		cows[cur[0]][cur[1]].adj++;
	    		cows[x][y].adj++;
	    		if(cows[x][y].adj == 3) {
	    			toProcess.add(addTempCow(new int[] {x, y}, cows));
	    			numTemp ++;
	    		}
	    	}
	    	
	    	y += 2;
	    	
	    	if(y < cows.length && cows[x][y] != null) {
	    		cows[cur[0]][cur[1]].adj++;
	    		cows[x][y].adj++;
	    		if(cows[x][y].adj == 3) {
	    			toProcess.add(addTempCow(new int[] {x, y}, cows));
	    			numTemp ++;
	    		}
	    	}
    		
    	}
    	
    	fout.append(numTemp).append("\n");
    	
    }
    
    System.out.print(fout);
    fin.close();
    
	}
}

class Cow {
	
	public boolean temp;
	public int adj;
	
	public Cow(boolean temporary, int adj) {
		
		this.temp = temporary;
		this.adj = adj;
		
	}
	
}