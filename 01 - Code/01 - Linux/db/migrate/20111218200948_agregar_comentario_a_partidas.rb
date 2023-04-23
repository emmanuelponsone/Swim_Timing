class AgregarComentarioAPartidas < ActiveRecord::Migration
  def self.up
    add_column :partidas, :comentario, :text
    
  end

  def self.down
    remove_column :partidas, :comentario
  end
end
