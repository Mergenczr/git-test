// Mergen Chinzorig
class Book{
    private String title, author;
    private int number;
    private double price;
    public Book (String title, String author, int pageCount,double price){
        this.title= title;
        this.author=author;
        this.number=pageCount;
        this.price=price;
    }

    public void read(){
        System.out.println("I am reading "+ title);
    }
    public void read (int a){
        System.out.println("I am reading "+ a +" pages of "+title);
    }

}

public class BookReader {
    public static void main(String[] args) {
        Book [] Booka = new Book [5];
        Book book1 = new Book("Title1", "Person1", 10,1.01 );
        Book book2= new Book("Title2", "Person2", 20,2.01 );
        Book book3= new Book("Title3", "Person3", 30,3.01 );

        Booka[0]=book1;
        Booka[1]=book2;
        Booka[2]=book3;

        book1.read();

        for(int i =0; i <Booka.length-2; i=i+1){
            Booka [i].read(10);
        }
    }
}