class MainController < TeacupWindowController
  stylesheet :main_window
  layout do
    @text_update = subview(NSTextField, :text_update,
                           stringValue: ''
                          )

    subview(NSButton, :update_button,
            action: 'update:',
            target: self,
           )

    scroll_view = subview(NSScrollView, :scroll_view)

    @table_view = subview(NSTableView, :table_view,
                          delegate: self,
                          dataSource: self,)

    column = NSTableColumn.alloc.initWithIdentifier("data")
    column.editable = false
    column.headerCell.setTitle("data")
    column.setWidth(290)
    @table_view.addTableColumn(column)
    scroll_view.setDocumentView(@table_view)
    
    @update_result = []

    @db = IndicoDB.new("Resources/test.json")
    #puts "[i] number of events: " + db.data.length.to_s
  end

  def numberOfRowsInTableView(aTableView)
    return 0 if @update_result.nil?
    return @update_result.size
  end

  def tableView(aTableView,
                objectValueForTableColumn: aTableColumn,
                row: rowIndex)
    case aTableColumn.identifier
    when "data"
      return @update_result[rowIndex].to_s
    end
  end

  def update(sender)
    text = @text_update.stringValue
    if text.length > 0      
      #@update_result = []
      @update_result.push(text)
      @db.each do |e|
           e.time_table.each do |tx|
                         @update_result.push(tx)
                       end
         end      
      @table_view.reloadData
    end
    #puts text
  end

end
