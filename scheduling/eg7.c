/* 7.Assume you own a small community bookstore that regularly needs to update its
inventory records at the end of the business day. The inventory update is divided into
two main tasks: tallying sales and restocking items. Due to the store's unique cataloging
system, these tasks need to be handled sequentially. Create a simple application that
uses UNIX/Linux processes, to separate the tallying of sales from the restocking of items.
Expected Output:
Parent Output: "Daily sales tallied successfully."
Child Output: "Items restocked based on sales data."
Final Output by Parent: "Inventory update complete."*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    pid_t pid = fork();
    if (pid == -1)
    {
        printf("Fork Failed\n");
        return 1;
    }
    else if (pid == 0)
    {
        printf("Child Output : \"Items restocked based on sales data.\"\n");
    }
    else
    {
        printf("Parent Output: \"Daily sales tallied successfully.\"\n");
        wait(NULL);
        printf("Final Output by Parent: \"Inventory update complete.\"\n");
    }
    return 0;
}