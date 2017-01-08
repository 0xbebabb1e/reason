#include <pebble.h>



static MenuLayer *s_menu_layer;



static uint16_t get_num_rows_callback(MenuLayer *menu_layer, 
                                      uint16_t section_index, void *context) {
  const uint16_t num_rows = 5;
  return num_rows;
}

static void draw_row_callback(GContext *ctx, const Layer *cell_layer, 
                                        MenuIndex *cell_index, void *context) {
  static char s_buff[16];
  snprintf(s_buff, sizeof(s_buff), "Row %d", (int)cell_index->row);

  // Draw this row's index
  //menu_cell_basic_draw(ctx, cell_layer, NULL, s_buff, NULL);
  menu_cell_basic_header_draw(ctx,cell_layer, s_buff);
}

static int16_t get_cell_height_callback(struct MenuLayer *menu_layer, 
                                        MenuIndex *cell_index, void *context) {
  const int16_t cell_height = 14;
  return cell_height;
}

int g_a = 0;

static void select_callback(struct MenuLayer *menu_layer, 
                                        MenuIndex *cell_index, void *context) {
  // Do something in response to the button press
  
  if (cell_index->row == 3){
    int a = 0;
    for (int i = 10, j=5;i==j +100;i/=j--) a++;
    g_a = a;
  }  


}
  
static Window *s_window;
static TextLayer *s_text_layer;

static void init(void) {

	// Create a window and get information about the window
	s_window = window_create();
  Layer *window_layer = window_get_root_layer(s_window);
  GRect bounds = layer_get_bounds(window_layer);
  
// Create the MenuLayer
s_menu_layer = menu_layer_create(bounds);

// Let it receive click events
menu_layer_set_click_config_onto_window(s_menu_layer, s_window);

// Set the callbacks for behavior and rendering
menu_layer_set_callbacks(s_menu_layer, NULL, (MenuLayerCallbacks) {
    .get_num_rows = get_num_rows_callback,
    .draw_row = draw_row_callback,
    .get_cell_height = get_cell_height_callback,
    .select_click = select_callback,
});

// Add to the Window
layer_add_child(window_get_root_layer(s_window), menu_layer_get_layer(s_menu_layer));
// Push the window, setting the window animation to 'true'
	window_stack_push(s_window, true);
}



static void deinit(void) {
// Destroy the MenuLayer
menu_layer_destroy(s_menu_layer);
  
}




int main(void) {
	init();
	app_event_loop();
	deinit();
}

