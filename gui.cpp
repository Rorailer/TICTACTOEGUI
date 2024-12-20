#include<iostream>
#include<vector>
#include<string>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include"Button/Button.hpp"

using namespace std;


//! Check if mouse is over a button.
bool isMouseOverText(const sf::Text &text, const sf::RenderWindow &window) {
    sf::FloatRect bounds = text.getGlobalBounds();
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return bounds.contains(static_cast<sf::Vector2f>(mousePos));
}



//! Pause Overlay
void overlay(sf::RenderWindow& window, sf::Font &font){
    
   


    sf::RectangleShape pause_overlay(sf::Vector2f(700,500));
    pause_overlay.setFillColor(sf::Color(225,225,225,225));
    pause_overlay.setPosition(50,50);

    window.draw(pause_overlay);

    }




//! Text to put over overlay if someone won or draw
void win(sf::RenderWindow& window,sf::Font& font, string whoWon , int playerWins , int compWins, bool& isPaused){

    //Text
    sf::Text winner;
    winner.setFont(font);
    winner.setString( whoWon + "Won!");
    winner.setStyle(sf::Text::Bold);
    winner.setPosition((window.getSize().x/2) - (winner.getGlobalBounds().width/2),150);

    //Button
    sf::Text Quit;
    Quit.setString("Quit!");
    Quit.setFont(font);
    Quit.setFillColor(sf::Color::Black);
    Quit.setStyle(sf::Text::Italic);
    Quit.setStyle(sf::Text::Underlined);
    Quit.setPosition(window.getSize().x/3,400);



    //Draw
    overlay(window,font);

    window.draw(winner);
    window.draw(Quit);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isMouseOverText(Quit, window)) {
        window.close();
    }
    else if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && isMouseOverText(winner, window)){
        isPaused == false;
    }


}







//! Computer Selecting cell
void AI(string (&arr)[9], string symbol){
    int x;
    do{
        srand(time(0));
        x = rand()%9;
    }while(arr[x]!="");
    arr[x] = symbol;

}


//! Vector AI
void VAI(vector<int>& cells , int& Random, vector<string>& buttonstate){
    srand(time(0));
    while(buttonstate[Random] != ""){

        int Index = rand() % cells.size();
        Random = cells[Index];
    }
    
    
        if (!cells.empty()) {

            cells.erase(remove(cells.begin(),cells.end(), Random), cells.end());

            buttonstate[Random] = "O";

            }
        else{}
}


//! Checking Winning
bool winchecklogic(vector<string>& buttonState, char symbol) {
    // Convert symbol to a string for comparison
    string symbolStr(1, symbol);

    // rows
    if ((buttonState[0] == symbolStr && buttonState[1] == symbolStr && buttonState[2] == symbolStr) ||
        (buttonState[3] == symbolStr && buttonState[4] == symbolStr && buttonState[5] == symbolStr) ||
        (buttonState[6] == symbolStr && buttonState[7] == symbolStr && buttonState[8] == symbolStr)) {
        return true;
    }

    // columns
    if ((buttonState[0] == symbolStr && buttonState[3] == symbolStr && buttonState[6] == symbolStr) ||
        (buttonState[1] == symbolStr && buttonState[4] == symbolStr && buttonState[7] == symbolStr) ||
        (buttonState[2] == symbolStr && buttonState[5] == symbolStr && buttonState[8] == symbolStr)) {
        return true;
    }

    // diagonals
    if ((buttonState[0] == symbolStr && buttonState[4] == symbolStr && buttonState[8] == symbolStr) ||
        (buttonState[2] == symbolStr && buttonState[4] == symbolStr && buttonState[6] == symbolStr)) {
        return true;
    }

    return false;
}


//! Logic to find who won.    Returns Who won
string who_Won(bool result, char symbol, int& draws, int& compWins, int& playerWins, int& compLoss, int& playerLoss){
    if(result){
        if(symbol == 'X'){
            playerWins++;
            compLoss++;
            return "Player";
        }else{
            compWins++;
            playerLoss++;
            return "Computer";
        }
    }else{return NULL;}

}


int main(){
    
    
    
    
    
    //*Variables

    vector<string> buttonstate = {"", "", "", "", "", "", "", "", ""};
    
    string buttonState[9] = {"", "", "", "", "", "", "", "", ""};
    vector<int> cells = {0,1,2,3,4,5,6,7,8};
    
    string p1Symbol = "X";
    string p2Symbol = "O";
    string compSymbol = "O";

    float lineThickness = 3;
    
    int p1Wins = 0;
    int p2Wins = 0;
    int p1Loss = 0;
    int p2Loss = 0;
    int draws = 0;
    int compWins = 0;
    int playerWins = 0;
    int compLoss = 0;
    int playerLoss = 0;

    //Colors
    int colour_lightgrey[4] = {211,211,211,100};
    int colour_invisible[4] = {211,211,211,2};

    //kinda variables. Shapes for pause button.
    sf::RectangleShape rect1, rect2,rect3;
    // *</Variables>
    
    
    // *Main Window Creation
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tic Tac Toe");
    window.setSize(sf::Vector2u(800,600));
    //*</Main Window>


    //*Font
    sf::Font font;
    if (!font.loadFromFile("timesnewromanbold.ttf")) {
        std::cout<< "Couldn't Load Font.";
    }
    //*</Font>
    
    
    //*Turn Text
    sf::Text playerTurn;
    playerTurn.setFont(font);
    playerTurn.setCharacterSize(15);
    playerTurn.setFillColor(sf::Color::White);
    playerTurn.setStyle(sf::Text::Bold);
    playerTurn.setStyle(sf::Text::Underlined);
    //*</Turn Text>
    
    
    
    
    
    
    //Loading Background Texture and setting vlaues
    
    /*
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("Background.jpeg");
    if (!backgroundTexture.loadFromFile("Background.jpeg")) {
        std::cout<< "Couldn't load texture.";
    }

    sf::Sprite Background;
    Background.setTexture(backgroundTexture);
    Background.setScale(800,600);
    */
    // Background.setPosition(0,0);

    //</Background>
    
    




    //*Creating Board 
    
    //Vertical Line 1
    sf::RectangleShape Vline1(sf::Vector2f(lineThickness,420));
    Vline1.setPosition(306.67,90);
    Vline1.setFillColor(sf::Color::White);


    //Vertical Line 2
    sf::RectangleShape Vline2(sf::Vector2f(lineThickness,420));
    Vline2.setPosition(493.33,90);
    Vline2.setFillColor(sf::Color::White);

    //Horizontal line 1
    sf::RectangleShape Hline1(sf::Vector2f(560,lineThickness));
    Hline1.setPosition(120,230);
    Hline1.setFillColor(sf::Color::White);

    //Horizontal line 2
    sf::RectangleShape Hline2(sf::Vector2f(560,lineThickness));
    Hline2.setPosition(120,370);
    Hline2.setFillColor(sf::Color::White);

    //*</Building Board>





    


    



    
    
    //*Variables in game loop
    bool paused = true;    
    int turn = 0;
    int compChoice;
    //*</Game loop variables>
    
    //! Game Loop
    while(window.isOpen()){
        
        string symbol;

       
        
        //*Creating Button and setting their positions.

        //Cell Buttons
        Button button00(buttonstate[0],font , 185.67 , 139, colour_invisible);
        Button button01(buttonstate[1],font , 185.67 , 139, colour_invisible);
        Button button02(buttonstate[2],font , 185.67 , 139, colour_invisible);
        Button button10(buttonstate[3],font , 185.67 , 139, colour_invisible);
        Button button11(buttonstate[4],font , 185.67 , 139, colour_invisible);
        Button button12(buttonstate[5],font , 185.67 , 139, colour_invisible);
        Button button20(buttonstate[6],font , 185.67 , 139, colour_invisible);
        Button button21(buttonstate[7],font , 185.67 , 139, colour_invisible);
        Button button22(buttonstate[8],font , 185.67 , 139, colour_invisible);
        button00.setPosition(120,90);
        button01.setPosition(305.67,90);
        button02.setPosition(491.33,90);
        button10.setPosition(120,229);
        button11.setPosition(305.67,229);
        button12.setPosition(491.33,229);
        button20.setPosition(120,368);
        button21.setPosition(305.67,368);
        button22.setPosition(491.33,368);

        //Pause Button
        Button pause_button("",font,15,10,colour_lightgrey);
        pause_button.setPosition(10,10);
        //*</Creating Button>


        //*Creating shapes for Puase button Image
        rect1.setFillColor(sf::Color::White);
        rect1.setSize(sf::Vector2f(5,15));
        rect1.setPosition(sf::Vector2f(2,2));
        
        rect2.setFillColor(sf::Color(0,0,0,0));
        rect2.setSize(sf::Vector2f(5,15));
        rect2.setPosition(sf::Vector2f(7,2));

        rect3.setFillColor(sf::Color::White);
        rect3.setSize(sf::Vector2f(5,15));
        rect3.setPosition(sf::Vector2f(12,2));
        //*</Pause button image>


        






        
        //^Selecting which one's have a turn.
        if(turn%2 == 0){
            
            symbol = p1Symbol;
            
            playerTurn.setString("Player's Turn");
            playerTurn.setPosition(((window.getSize().x/2)-(playerTurn.getLocalBounds().width/2)),20);

        }else{
            
            
            symbol = compSymbol;
            

            playerTurn.setString("Computer's Turn");
            playerTurn.setPosition(((window.getSize().x/2)-(playerTurn.getLocalBounds().width/2)),20);
            
            }
        

        
        //^Event Loop
        sf::Event event;
        while(window.pollEvent(event)){
            
            //^CHeck if user clicks close button.
            if(event.type == sf::Event::Closed){
                window.close();
            }
            

            //^ If computer's turn use AI.
            if(symbol == compSymbol){

                VAI(cells,compChoice,buttonstate);

                // AI(buttonstate, symbol);
                turn++;
            
            }
            
            //^ If left click registerd, check Which button was pressed.
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left){
                    if(button00.isPressed(sf::Mouse::getPosition(window))){
                        buttonstate[0] = symbol;
                        turn++;
                    }
                    else if(button01.isPressed(sf::Mouse::getPosition(window))){
                        buttonstate[1] = symbol;
                        turn++;
                    }
                    else if(button02.isPressed(sf::Mouse::getPosition(window))){
                        buttonstate[2] = symbol;
                        turn++;
                    }
                    else if(button10.isPressed(sf::Mouse::getPosition(window))){
                        buttonstate[3] = symbol;
                        turn++;
                    }
                    else if(button11.isPressed(sf::Mouse::getPosition(window))){
                        buttonstate[4] = symbol;
                        turn++;
                    }
                    else if(button12.isPressed(sf::Mouse::getPosition(window))){
                        buttonstate[5] = symbol;
                        turn++;
                    }
                    else if(button20.isPressed(sf::Mouse::getPosition(window))){
                        buttonstate[6] = symbol;
                        turn++;
                    }
                    else if(button21.isPressed(sf::Mouse::getPosition(window))){
                        buttonstate[7] = symbol;
                        turn++;
                    }
                    else if(button22.isPressed(sf::Mouse::getPosition(window))){
                        buttonstate[8] = symbol;
                        turn++;
                    }
                    else if(pause_button.isPressed(sf::Mouse::getPosition(window))){
                        paused = true;
                        while(paused){

                            sf::Event pauseEvent;
                            while(window.pollEvent(pauseEvent)){
                                if(pauseEvent.type == sf::Event::Closed){
                                    window.close();
                                    paused = false;
                                }
                            }

                            window.clear(sf::Color::Black);
                            win(window,font,"No One",playerWins,compWins,paused);
                            window.display();
    }                   
                    }
                    else{}
                    



                }//close if of "WHich " button pressed
                
                }//Clossing if a button pressed
                else{}



        }//EVen while close

        
       

        //Check if Someone Won
        bool result = winchecklogic(buttonstate, symbol[0]);
        
        //If comeone Won
        if(result){

            //Updates variables accoring to who won
            who_Won(result, symbol[0], draws, compWins, playerWins, compLoss, playerLoss);
            
            //reset turn count
            turn = 0;
            //reset board.
            for(int i = 0; i<9 ; i++){
                buttonstate[i] = "";
            }
        }
        


        

    
        



        //*Update window
        window.clear(sf::Color::Black);
        //*</Update Window>

        //*Table Display.
        window.draw(Vline1); 
        window.draw(Vline2);

        window.draw(Hline1); 
        window.draw(Hline2);

        //*</Table>


        
        //*Display turn
        window.draw(playerTurn);
        //*</Display Tunr>


        //*Buttons
        button00.draw(window);
        button01.draw(window);
        button02.draw(window);
        button10.draw(window);
        button11.draw(window);
        button12.draw(window);
        button20.draw(window);
        button21.draw(window);
        button22.draw(window);
        //*</Buttons>

        //*Pause Button
        window.draw(rect1);
        window.draw(rect2);
        window.draw(rect3);
        pause_button.draw(window);
        //*</Pause Button>

        window.display();

        
        }   //Game Loop 
} // Main Loop  