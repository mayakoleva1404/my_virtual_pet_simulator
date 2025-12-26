#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

//Константи
#define TOTAL_DAYS 10 // - брой дни в играта
#define MAX_STAT 10 //- максимална стойност за всяка статистика
#define MIN_STAT  0 // - минимална стойност за всяка статистика
#define MAX_NAME_LENGTH 20 // -  максимална дължина на името на котката

// структура на котката
typedef struct {
    char name [MAX_NAME_LENGTH];
    int happiness;
    int hunger;
    int health;
    int cleanliness;
    int energy;
    int score;
    int daysSurvived;
} Cat;

//декларация на функции
void initialize_cat(Cat *cat); // - инициализация на котката - задава име и начални стойности
void show_status(Cat *cat, int day);   //показва статуса за деня
void draw_cat(Cat *cat);  // рисува ASCII котка
void show_menu();  //показва менюто с възможни действия
int get_action(); // взима действие от потребителя
void feed(Cat *cat);
void play(Cat *cat);
void rest(Cat *cat);
void clean(Cat *cat);
void validate_stats(Cat *cat); //ограничава статистиките 0-10
void day_effects(Cat *cat); // дневни пасивни ефекти
bool check_game_end(Cat *cat); // проверява дали играта е свършила
void print_final_results(Cat *cat); // печата крайните резултати


//главна функция
int main(){
    // - генератор на случайни числа
    srand(time(NULL));

    printf("Welcome to your virtual cat simulator!\n");
    printf("The fate of your cat lies in your hands for %i days!\n",TOTAL_DAYS);

    //създаване на котката
    Cat my_cat;
    initialize_cat(&my_cat);

    // главен цикъл
    for (int day = 1; day <= TOTAL_DAYS; day++){

        // покаване на статуса
        show_status(&my_cat, day);

        //рисуване на котката
        draw_cat(&my_cat);

        //показване на менюто
        show_menu();

        //предприемане на действие от потребителя
        int action = get_action();

        //изпълняване на действието
        switch(action){
            case 1:
              feed(&my_cat);
              break;
            case 2:
              if(my_cat.energy >= 2){// проверяваме дали котката има енергия
                 play(&my_cat);
              }
              else{
                printf("%s is too tired to play!\n", my_cat.name);
              }
              break;
            case 3:
              rest(&my_cat);
              break;
            case 4:
              clean(&my_cat);
              break;
            default:
              printf("You decided to do nothing today.\n");

              //намаляване на точките за бездействие
             if(my_cat.score > 0) {
                 my_cat.score--;
             }
              break;
        }
        //валидиране на статистиките
        validate_stats(&my_cat);
        //дневни ефекти
        day_effects(&my_cat);

        //поверка дали играта свършва
        if(check_game_end(&my_cat)){
          my_cat.daysSurvived = day;
          print_final_results(&my_cat);
          return 0; // край на играта
        }
        // Ако е последният ден от играта:
        if (day == TOTAL_DAYS) {
          printf("\n Congrats! %s survived all %d days!\n",my_cat.name, TOTAL_DAYS);
          my_cat.daysSurvived = day;
          print_final_results(&my_cat);
        }
      }//край на форцикъла

    return 0;
}

void initialize_cat(Cat *cat){
  //Питаме потребителя за име на котката
  string name = get_string("What's your cat's name?");

  // Копираме името символ по символ
  int i =0;
  while (name[i] != '\0' && i < MAX_NAME_LENGTH -1 ){
    cat-> name[i] = name[i];
    i++;
  }
  cat->name[i] ='\0'; // терминиране на стринга

  //Задаване на начални стойности на всички статистики
  cat -> happiness = 5;
  cat -> hunger = 5;
  cat -> health = 5;
  cat -> cleanliness = 5;
  cat -> energy = 5;
  cat -> score = 0;
  cat-> daysSurvived = 0;

  printf("\nWelcome!, %s! Let's take good care of you!\n", cat->name);
}
 void show_status(Cat *cat, int day) {
  printf("\n-------Day %d -------\n", day);
  printf("Hunger: %d | Happiness: %d | Health: %d | Energy: %d | Cleanliness: %d\n ", cat->hunger, cat->happiness, cat->health, cat->energy, cat->cleanliness);
 }

 void draw_cat(Cat *cat){
  printf("\n"); // добавен е празен ред за разстояние
  // проверка на условията по приоритет
  if (cat->health <= 3) {
    printf(" /\\_/\\\n( x_x )  I feel sick...\n > ^ <\n");
  }
  else if (cat->hunger >=8){
    printf(" /\\_/\\\n( T_T )  I'm starving!\n > ^ <\n");
  }
  else if (cat-> happiness >=7 && cat-> energy >= 5){
    printf(" /\\_/\\\n( ^_^ )  I'm so happy!\n > ^ <\n");
  }
  else if(cat->cleanliness <=3){
    printf(" /\\_/\\\n( o_o )  I need a bath...\n > ^ <\n");
  }
  else if(cat->energy <= 3){
    printf(" /\\_/\\\n( -.- )  So sleepy...\n zZZ\n");
  }
  else{
    printf(" /\\_/\\\n( o.o )  Just relaxing.\n > ^ <\n");
  }
  printf("\n");
 }

 void show_menu(){
  printf("Available actions:\n");
  printf("1. Feed\n");
  printf("2. Play\n");
  printf("3. Rest\n");
  printf("4. Clean cat\n\n");
 }
 int get_action(){
  int action;

  //while - цикъл за валидация
  while(true){
    action = get_int("Choose action (1-4):");
    //приемаме всяко число
    if(action >= 1 && action <= 4 ) {
      break;
    }

    printf("Please enter a number between 1 and 4!\n");
  }

  return action;
 }

 void feed (Cat *cat) {
  printf("YAY! You fed your cat successfully!\n");
  cat->hunger -= 3;
  cat -> cleanliness -= 1;
  cat -> score += 3 ;
 }

 void play (Cat *cat) {
  printf("LET'S GOO! You played with ur cat and it's now very happy!\n");
  cat->happiness += 2 ;
  cat->energy -= 2;
  cat->health -= 1;
  cat->score += 5;
 }

 void rest (Cat *cat) {
  printf("Your cat took a nap!\n");
  cat->energy += 3;
  cat->health += 1;
  cat->score += 2;
 }

 void clean (Cat *cat) {
  printf("YIPPY! You have finally cleaned your cat!\n");
  cat->cleanliness += 3;
  cat->score += 2;
 }
 void validate_stats(Cat *cat) {
  //масив от указатели към всички статистики
  int *stats[] = {
    &cat-> happiness,
    &cat->hunger,
    &cat->health,
    &cat->energy,
    &cat->cleanliness
  };

  //for цикъл за проверка на всяка статистика
  for(int i = 0; i<5; i++) {
    if(*stats[i] >MAX_STAT) {
      *stats[i] = MAX_STAT;
    }
    else if(*stats[i] <MIN_STAT) {
      *stats[i] = MIN_STAT;
    }
  }
 }

 void day_effects(Cat *cat) {
  cat->hunger += 1;
  cat->energy -= 1;
  cat->cleanliness -= 1;

  if(cat->cleanliness < 3) {
    cat->health -= 1;
  }
  if(cat->hunger > 8) {
    cat->health -= 1;
  }
  //случайно събитие - 10% вероятност да се случи
  if(rand()%10 == 0) {
    //котката е консумирала развалена храна и я боли коремчето
    printf("OH,NOO! %s ate a leftover from yesterday's dinner! It was a spoiled piece of chicken, so now its tummy hurts!\n", cat-> name);
    cat->health -= 2;// намаляване на показателя за здраве поради натравяне.
    cat->hunger -= 2; //намаляне на глада, защото котката все пак е приела храна.
  }
 }

 bool check_game_end(Cat *cat) {
  // връща TRUE ако играта трябва да свърши
  //връща FALSE ако играта продължава

  //първа проверка - глад
  if (cat->hunger >=10) {
    printf("OOH! Your cat starved!\n");
    return true; //край на играта
  }

  //втора проверка - ако е твърде тъжна
  if (cat->happiness <=0) {
    printf("OOPS! Your cat became 2 sad and ran away!\n");
    return true; //край на играта
  }

  //трета проверка - ако е твърде болна
  if (cat->health <=0) {
    printf("Sadly, your cat became 2 sick and died! Now u no longer own a pet:((\n");
    return true;//край на играта
  }
  return false;
 }

 void print_final_results(Cat *cat) {
  printf("\n====== GAME SUMMARY ======\n");
  //показва колко дни е оцеляла
  printf("Days survived:%i\n", cat->daysSurvived);
  // крайни статистики
  printf("Final Stats:\n");
  printf("Hunger: %i | Happiness: %i | Health: %i | Energy: %i | Cleanliness: %i \n", cat->hunger, cat->happiness, cat->health, cat->energy, cat->cleanliness );

//проверява крайните статистики и дава коментар
  if(cat->health > 7 && cat->happiness > 7) {
    printf("You did a great job;) Your cat lived an amazing life!\n");
  }
  else if (cat-> health < 4) {
    printf("Your cat wasn't very happy but tried its best.\n");
  }
  else {
    printf("Your cat had a boring but safe life.\n");
  }

  //краен резултат
  printf("\nFinal score: %d\n" , cat->score);
 }
