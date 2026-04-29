#include <stdio.h>
#include <string.h>

#define MAX 100
#define MAX_BUDGET 1000

// ---------------- STRUCT ----------------
typedef struct {
    char name[60];
    int cost;
    int protein;
    int calories;
    int veg;
    char category[20];
} MealCombo;

// ---------------- DATASET ----------------
MealCombo combos[] = {

    // BREAKFAST
    {"Idli + Sambar + Chutney", 50, 6, 180, 1, "breakfast"},
    {"Dosa + Chutney + Milk", 60, 8, 250, 1, "breakfast"},
    {"Oats + Milk + Fruits", 55, 9, 220, 1, "breakfast"},
    {"Bread + Butter + Milk", 45, 6, 210, 1, "breakfast"},
    {"Eggs + Toast + Juice", 70, 12, 260, 0, "breakfast"},
    {"Poha + Tea", 40, 4, 180, 1, "breakfast"},
    {"Boiled Eggs + Milk", 60, 12, 180, 0, "breakfast"},
    {"Egg Sandwich + Tea", 70, 10, 220, 0, "breakfast"},
    {"Omelette + Bread", 65, 11, 210, 0, "breakfast"},

    // LUNCH
    {"Rice + Dal + Curd", 80, 12, 350, 1, "lunch"},
    {"Roti + Paneer Curry", 110, 18, 400, 1, "lunch"},
    {"Veg Biryani + Raita", 120, 10, 450, 1, "lunch"},
    {"Fried Rice + Manchurian", 130, 12, 500, 1, "lunch"},
    {"Chicken Biryani + Salad", 150, 22, 550, 0, "lunch"},
    {"Egg Curry + 2 Roti", 90, 14, 320, 0, "lunch"},
    {"Chicken Curry (Small) + Roti", 95, 16, 350, 0, "lunch"},
    {"Egg Fried Rice (Half)", 85, 12, 300, 0, "lunch"},

    // DINNER
    {"Roti + Dal Tadka + Veg", 100, 15, 380, 1, "dinner"},
    {"Paneer + Roti + Salad", 120, 20, 420, 1, "dinner"},
    {"Grilled Chicken + Rice", 160, 30, 500, 0, "dinner"},
    {"Fish Curry + Rice", 150, 25, 480, 0, "dinner"},
    {"Soy Chunk Curry + Roti", 110, 22, 400, 1, "dinner"},
    {"Egg Curry + Rice", 120, 18, 450, 0, "dinner"},
    {"Egg Curry + Rice (Small)", 95, 15, 340, 0, "dinner"},
    {"Chicken Soup + Bread", 80, 10, 200, 0, "dinner"},
    {"Egg Bhurji + Roti", 90, 13, 310, 0, "dinner"}
};

int n = sizeof(combos) / sizeof(combos[0]);

// ---------------- VALUE FUNCTION ----------------
float getValue(MealCombo item) {
    return item.protein * 2 + item.calories * 0.1;
}

// ---------------- FILTER ----------------
int filterItems(MealCombo filtered[], int veg_only, char meal_type[]) {
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (veg_only && combos[i].veg == 0)
            continue;

        if (strcmp(meal_type, "all") != 0 &&
            strcmp(combos[i].category, meal_type) != 0)
            continue;

        filtered[count++] = combos[i];
    }

    return count;
}

// ---------------- DISPLAY ----------------
void displayItems(MealCombo items[], int count) {
    int totalCost = 0, totalProtein = 0, totalCalories = 0;
    float totalValue = 0;

    for (int i = 0; i < count; i++) {
        printf("• %s (₹%d, Protein:%dg, Calories:%d)\n",
               items[i].name,
               items[i].cost,
               items[i].protein,
               items[i].calories);

        totalCost += items[i].cost;
        totalProtein += items[i].protein;
        totalCalories += items[i].calories;
        totalValue += getValue(items[i]);
    }

    printf("\nTotal Cost: ₹%d", totalCost);
    printf("\nTotal Protein: %dg", totalProtein);
    printf("\nTotal Calories: %d", totalCalories);
    printf("\nNutrition Score: %.2f\n", totalValue);
}

// ---------------- SORT FOR BINARY SEARCH ----------------
void sortByName(MealCombo arr[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(arr[j].name, arr[j + 1].name) > 0) {
                MealCombo temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// ---------------- BINARY SEARCH ----------------
int binarySearch(MealCombo arr[], int count, char target[]) {
    int low = 0, high = count - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        int cmp = strcmp(arr[mid].name, target);

        if (cmp == 0)
            return mid;
        else if (cmp < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

// ---------------- GREEDY ----------------
void greedy(MealCombo items[], int count, int budget) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            float r1 = getValue(items[j]) / items[j].cost;
            float r2 = getValue(items[j + 1]) / items[j + 1].cost;

            if (r1 < r2) {
                MealCombo temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }

    MealCombo selected[MAX];
    int selCount = 0, totalCost = 0;

    for (int i = 0; i < count; i++) {
        if (totalCost + items[i].cost <= budget) {
            selected[selCount++] = items[i];
            totalCost += items[i].cost;
        }
    }

    printf("\n--- GREEDY APPROACH ---\n");
    displayItems(selected, selCount);
}

// ---------------- DP ----------------
void dp(MealCombo items[], int count, int budget, MealCombo selected[], int *selCount) {
    float dp[MAX][MAX_BUDGET] = {0};

    for (int i = 1; i <= count; i++) {
        for (int w = 0; w <= budget; w++) {
            if (items[i - 1].cost <= w) {
                float include = getValue(items[i - 1]) +
                                dp[i - 1][w - items[i - 1].cost];
                float exclude = dp[i - 1][w];
                dp[i][w] = (include > exclude) ? include : exclude;
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int w = budget;
    *selCount = 0;

    for (int i = count; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            selected[(*selCount)++] = items[i - 1];
            w -= items[i - 1].cost;
        }
    }

    printf("\n--- DYNAMIC PROGRAMMING (OPTIMAL) ---\n");
    displayItems(selected, *selCount);

    printf("\nOptimal Score: %.2f\n", dp[count][budget]);
}

// ---------------- WEEKLY PLAN ----------------
void weeklyBuffet(MealCombo items[], int count) {
    char *days[] = {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};

    printf("\n🍱 WEEKLY BUFFET PLAN:\n\n");

    for (int d = 0; d < 7; d++) {
        printf("%s:\n", days[d]);

        int b=-1, l=-1, din=-1;

        for (int i = 0; i < count; i++) {
            int idx = (i + d) % count;

            if (b == -1 && strcmp(items[idx].category, "breakfast") == 0)
                b = idx;
            else if (l == -1 && strcmp(items[idx].category, "lunch") == 0)
                l = idx;
            else if (din == -1 && strcmp(items[idx].category, "dinner") == 0)
                din = idx;
        }

        if (b != -1) printf("  🍳 %s\n", items[b].name);
        if (l != -1) printf("  🍛 %s\n", items[l].name);
        if (din != -1) printf("  🍽 %s\n", items[din].name);

        printf("\n");
    }
}

// ---------------- MAIN ----------------
int main() {
    int budget, veg_choice;
    char meal_type[20];

    printf("🍱 SMART BUFFET MEAL PLANNER\n");

    printf("Enter budget (₹): ");
    scanf("%d", &budget);

    if (budget <= 0 || budget > MAX_BUDGET) {
        printf("Invalid budget ❌\n");
        return 0;
    }

    printf("Veg only? (1=Yes, 0=No): ");
    scanf("%d", &veg_choice);

    printf("Meal type (breakfast/lunch/dinner/all): ");
    scanf("%s", meal_type);

    MealCombo filtered[MAX];
    int count = filterItems(filtered, veg_choice, meal_type);

    if (count == 0) {
        printf("No combos available ❌\n");
        return 0;
    }

    // Greedy
    MealCombo greedy_items[MAX];
    for (int i = 0; i < count; i++)
        greedy_items[i] = filtered[i];

    greedy(greedy_items, count, budget);

    // DP
    MealCombo dp_selected[MAX];
    int dp_count = 0;

    dp(filtered, count, budget, dp_selected, &dp_count);

    // Weekly Plan
    weeklyBuffet(dp_selected, dp_count);

    // ---------------- SEARCH ----------------
    char searchName[60];

    printf("\n🔍 Enter combo name to search: ");
    scanf(" %[^\n]", searchName);

    sortByName(filtered, count);

    int index = binarySearch(filtered, count, searchName);

    if (index != -1) {
        printf("\n✅ Found Combo:\n");
        printf("%s (₹%d, Protein:%dg, Calories:%d)\n",
               filtered[index].name,
               filtered[index].cost,
               filtered[index].protein,
               filtered[index].calories);
    } else {
        printf("❌ Combo not found\n");
    }

    return 0;
}
