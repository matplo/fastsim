Teacup::Stylesheet.new :main_window do

  style :text_update,
    frame: NSMakeRect(20, 318, 341, 22),
    autoresizingMask: autoresize.fill_top

  style :update_button,
    frame: NSMakeRect(384, 310, 82, 32),
    title: "Update",
    bezelStyle: NSRoundedBezelStyle,
    autoresizingMask: autoresize.fixed_top_right

  style :scroll_view,
    frame: NSMakeRect(0, 0, 480, 300),
    autoresizingMask: autoresize.fill,
    hasVerticalScroller: true

  style :table_view,
    autoresizingMask: autoresize.fill

end
