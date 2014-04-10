class MainController < TeacupWindowController
  stylesheet :main_window

  layout do
    @text_search = subview(NSTextField, :text_search,
                           stringValue: ''
                          )
    subview(NSButton, :search_button,
            action: 'search:',
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
  end

  def numberOfRowsInTableView(aTableView)
    return 0 if @search_result.nil?
    return @search_result.size
  end

  def tableView(aTableView,
                objectValueForTableColumn: aTableColumn,
                row: rowIndex)
    case aTableColumn.identifier
    when "data"
      return @search_result[rowIndex].to_s
    end
  end

  def search(sender)
    text = @text_search.stringValue
    if text.length > 0      
      @search_result = []      
      @search_result.push(text)
      @table_view.reloadData
    end
    puts text
  end

  def textView(aText)
    return "some text"
  end
end
