int main() {

    double previous = getCurrentTime();
    double lag = 0.0;
    while(true) { // consider rather while(!done)
        double current = getCurrentTime();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;
        
        processInput();
        
        while (lag >= MS_PER_UPDATE) {
            update();
            lag -= MS_PER_UPDATE;
        }
        render(lag / MS_PER_UPDATE); // parameter to extrapolate behaviour of objects if rendering somewhere in-between updates
    }
}