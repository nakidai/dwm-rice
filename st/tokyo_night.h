/* Terminal colors (16 first used in escape sequence) */
static const char *colorname[] = {
    /* 8 normal colors */
    [0] = "#1a1b26", /* black   */
    [1] = "#f7768e", /* red     */
    [2] = "#9ece6a", /* green   */
    [3] = "#e0af68", /* yellow  */
    [4] = "#2ac3de", /* blue    */
    [5] = "#bb9af7", /* magenta */
    [6] = "#7dcfff", /* cyan    */
    [7] = "#d5d6db", /* white   */
                                  
    /* 8 bright colors */
    [8]  = "#1a1b26", /* black   */
    [9]  = "#f7768e", /* red     */
    [10] = "#9ece6a", /* green   */
    [11] = "#e0af68", /* yellow  */
    [12] = "#2ac3de", /* blue    */
    [13] = "#bb9af7", /* magenta */
    [14] = "#7dcfff", /* cyan    */
    [15] = "#cfc9c2", /* white   */
                                   
    /* special colors */
    [256] = "#1a1b26", /* background */
    [257] = "#cfc9c2", /* foreground */

};

unsigned int defaultfg = 257;
unsigned int defaultbg = 256;
unsigned int defaultcs = 257;
static unsigned int defaultrcs = 257;
