/*
ID: andwerp1
LANG: JAVA
TASK: rental
*/

package rental;

import java.io.*;
import java.util.*;

class rentalver1 {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("rental.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("rental.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int m = Integer.parseInt(st.nextToken());
    int r = Integer.parseInt(st.nextToken());
    
    int[] cows = new int[n];
    int[][] buyOffers = new int[m][2];
    int[] rentals = new int[r];
    
    for(int i = 0; i < n; i++) {
    	
    	cows[i] = Integer.parseInt(fin.readLine());
    	
    }
    
    for(int i = 0; i < m; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	buyOffers[i][0] = Integer.parseInt(st.nextToken());
    	buyOffers[i][1] = Integer.parseInt(st.nextToken());
    	
    }
    
    for(int i = 0; i < r; i++) {
    	
    	rentals[i] = Integer.parseInt(fin.readLine());
    	
    }
    
    Arrays.sort(cows);
    Arrays.sort(buyOffers, (a, b) -> a[1] - b[1]);
    Arrays.sort(rentals);
    
    int rentalPointer = rentals.length - 1;
    int buyPointer = buyOffers.length - 1;
    
    int totalMoney = 0;
    
    System.out.println("rent pointer: " + rentalPointer + " buy pointer: " + buyPointer);
    
    for(int i = cows.length - 1; i > -1; i--) {
    	
    	int rentalMoney = 0;
    	
    	if(rentalPointer >= 0) {
    		rentalMoney = rentals[rentalPointer];
    		
    	}
    	
    	
    	int buyMoney = 0;
    	
    	int numGallons = cows[i];
    	
    	int tempBuyPointer = buyPointer;
    	int gallonsRemaining = buyOffers[buyPointer][0];
    	
    	while(numGallons != 0 && (tempBuyPointer >= 0 && buyOffers[0][0] != 0)) {
    		
    		System.out.println("gallons remaining: " + gallonsRemaining);
    		
    		if(gallonsRemaining >= numGallons) {
    			
    			buyMoney += numGallons * buyOffers[tempBuyPointer][1];
    			gallonsRemaining -= numGallons;
    			numGallons = 0;
    			
    		}
    		
    		else {
    			
    			buyMoney += gallonsRemaining * buyOffers[tempBuyPointer][1];
    			numGallons -= gallonsRemaining;
    			tempBuyPointer --;
    			gallonsRemaining = buyOffers[tempBuyPointer][0];
    			
    		}
    		
    	}
    	
    	if(rentalMoney > buyMoney) {
    		
    		totalMoney += rentalMoney;
    		rentalPointer --;
    		
    		//System.out.println("cow: " + i + " rental money: " + rentalMoney);
    		
    	}
    	
    	else {
    		
    		totalMoney += buyMoney;
    		buyPointer = tempBuyPointer;
    		buyOffers[buyPointer][0] = gallonsRemaining;
    		
    		//System.out.println("cow: " + i + " buy money: " + buyMoney);
    		
    	}
    	
    	System.out.println("cow: " + i + " buy money: " + buyMoney + " rental money: " + rentalMoney);
    	System.out.println("rent pointer: " + rentalPointer + " buy pointer: " + buyPointer + " gallons remaining: " + buyOffers[buyPointer][0]);
    	
    }
    
    fout.println(totalMoney);
    
    fin.close();
    fout.close();
    
	}
}