class ListTest{
   public static void main(String[] args){
      List A = new List();
      List B = new List();
       
     
      for(int i=1; i<=2; i++){
         A.append(i);
       } 
   System.out.println(); 
   List C = A.copy(); 
   System.out.println("TESTING COPY");
   System.out.println(A);
   System.out.println(C);
   System.out.println("A.length = "+A.length());
   System.out.println("C.length = "+C.length());
   System.out.println("TESTING EQUALS");
   System.out.println(A.equals(B)); 
   } 
}


