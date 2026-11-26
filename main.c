
#include <stdio.h>

int main() {

    int budget, total = 0, balance, i;
    int expense[4];

    char *category[] = {
        "Food", "Travel", "Shopping", "Other"
    };

    char *status;
    char *color;
    char *message;

    printf("\n=============================\n");
    printf("       POCKETPILOT v1.0       \n");
    printf("   Smart Expense Tracker     \n");
    printf("=============================\n");

    // Take budget input
    printf("Enter monthly budget: Rs. ");

    if (scanf("%d", &budget) != 1 || budget <= 0) {
        printf("Invalid budget!\n");
        return 1;
    }

    // Take expenses using a loop
    for (i = 0; i < 4; i++) {
        printf("Enter %s expense: Rs. ", category[i]);

        if (scanf("%d", &expense[i]) != 1 ||
            expense[i] < 0 || expense[i] > 100000000) {
            printf("Invalid expense!\n");
            return 1;
        }

        total = total + expense[i];
    }

    // Calculate remaining balance
    balance = budget - total;

    // Check financial status
    if (balance >= 0) {
        status = "Within Budget";
        color = "#66E5B1";
        message = "Great job! Your expenses are within budget.";
    } else {
        status = "Over Budget";
        color = "#F87171";
        message = "Warning! You need to reduce your expenses.";
    }

    // Display results in terminal
    printf("\n-------- MONTHLY REPORT --------\n");
    printf("Budget:    Rs. %d\n", budget);
    printf("Expenses:  Rs. %d\n", total);
    printf("Remaining: Rs. %d\n", balance);
    printf("Status:    %s\n", status);

    // Create HTML file
    FILE *fp = fopen("index.html", "w");

    if (fp == NULL) {
        printf("Unable to create HTML file.\n");
        return 1;
    }

    // HTML structure and CSS design
    fputs(
        "<!DOCTYPE html>"
        "<html lang='en'><head>"
        "<meta charset='UTF-8'>"
        "<meta name='viewport' content='width=device-width, initial-scale=1'>"
        "<title>PocketPilot | Expense Tracker</title>"

        "<style>"
        "*{box-sizing:border-box;}"
        "body{background:#0F172A;color:white;"
        "font-family:Arial,sans-serif;padding:20px;}"
        ".container{max-width:900px;margin:auto;}"
        "h1{color:#66E5B1;font-size:42px;margin-bottom:5px;}"
        ".subtitle{color:#94A3B8;letter-spacing:2px;}"
        ".cards{display:flex;gap:15px;flex-wrap:wrap;"
        "margin:30px 0;}"
        ".card{background:#1E293B;padding:22px;"
        "border-radius:18px;flex:1;min-width:180px;"
        "border:1px solid #334155;}"
        ".card p{color:#94A3B8;margin-top:0;}"
        ".card h2{font-size:30px;}"
        ".panel{background:#1E293B;padding:25px;"
        "border-radius:18px;margin-top:20px;}"
        ".item{display:flex;justify-content:space-between;}"
        "progress{width:100%;height:12px;"
        "accent-color:#66E5B1;margin-bottom:15px;}"
        "footer{text-align:center;color:#94A3B8;"
        "margin-top:35px;font-size:13px;}"
        "</style></head><body>"

        "<div class='container'>"
        "<h1>PocketPilot.</h1>"
        "<p class='subtitle'>SMART STUDENT FINANCE</p>"
        "<hr style='border:1px solid #334155'>"
        "<h3>Monthly Financial Overview</h3>"
        "<div class='cards'>", fp
    );

    // Insert calculated values into HTML
    fprintf(fp,
        "<div class='card'><p>Monthly Budget</p>"
        "<h2>&#8377;%d</h2></div>", budget);

    fprintf(fp,
        "<div class='card'><p>Total Expenses</p>"
        "<h2 style='color:#FDBA74'>&#8377;%d</h2></div>",
        total);

    fprintf(fp,
        "<div class='card'><p>Remaining Balance</p>"
        "<h2 style='color:%s'>&#8377;%d</h2></div>",
        color, balance);

    fputs("</div><div class='panel'>"
          "<h2>Expense Breakdown</h2>", fp);

    // Generate expense progress bars
    for (i = 0; i < 4; i++) {

        fprintf(fp,
            "<div class='item'>"
            "<p>%s</p><p>&#8377;%d</p></div>"
            "<progress value='%d' max='%d'></progress>",
            category[i], expense[i],
            expense[i], total > 0 ? total : 1);
    }

    // Display financial status
    fprintf(fp,
        "</div><div class='panel'>"
        "<h2 style='color:%s'>%s</h2>"
        "<p>%s</p></div>",
        color, status, message);

    // Footer
    fputs(
        "<footer>"
        "Designed by Jigisha Chopra<br>"
        "BCA Artificial Intelligence | Bennett University<br>"
        "Built using C, HTML and CSS"
        "</footer></div></body></html>", fp
    );

    fclose(fp);

    printf("\nDashboard created successfully!\n");
    printf("Open index.html in your browser.\n");

    return 0;
}
