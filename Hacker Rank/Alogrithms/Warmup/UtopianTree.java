import java.io.*;
import java.util.*;

// https://www.hackerrank.com/challenges/utopian-tree

public class Solution {

  public static void getTreeHeightAfterCycles(int[] array,int size){
		for(int i = 0; i < size; i++) {
			int height=1;
			if(array[i]!=0){
				for(int j=1;j<=array[i];j++){
					if(j%2==0){
						 height+=1;
					}else{
						 height*=2;
					}
				}
			}
			System.out.println(height);
		}
	}
    
    
      
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
       int s = in.nextInt();
       int[] ar = new int[s];
       for(int i=0;i<s;i++){
            ar[i]=in.nextInt(); 
       }
      getTreeHeightAfterCycles(ar,ar.length);    
                    
    } 
}

